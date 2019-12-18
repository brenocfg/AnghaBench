#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* data; int len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_9__ {TYPE_3__* binary_patch; int /*<<< orphan*/  prop_patches; } ;
typedef  TYPE_2__ svn_patch_t ;
typedef  void* svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_10__ {scalar_t__ src_end; scalar_t__ dst_end; scalar_t__ src_start; scalar_t__ dst_start; void* dst_filesize; void* src_filesize; int /*<<< orphan*/ * apr_file; } ;
typedef  TYPE_3__ svn_diff_binary_patch_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  void* apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SET ; 
 int /*<<< orphan*/  APR_SIZE_MAX ; 
 int /*<<< orphan*/  APR_UINT64_MAX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/ * svn_cstring_strtoui64 (void**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_readline (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int svn_stringbuf_first_non_whitespace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
parse_binary_patch(svn_patch_t *patch, apr_file_t *apr_file,
                   svn_boolean_t reverse,
                   apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_off_t pos, last_line;
  svn_stringbuf_t *line;
  svn_boolean_t eof = FALSE;
  svn_diff_binary_patch_t *bpatch = apr_pcalloc(result_pool, sizeof(*bpatch));
  svn_boolean_t in_blob = FALSE;
  svn_boolean_t in_src = FALSE;

  bpatch->apr_file = apr_file;

  patch->prop_patches = apr_hash_make(result_pool);

  SVN_ERR(svn_io_file_get_offset(&pos, apr_file, scratch_pool));

  while (!eof)
    {
      last_line = pos;
      SVN_ERR(svn_io_file_readline(apr_file, &line, NULL, &eof, APR_SIZE_MAX,
                               iterpool, iterpool));

      /* Update line offset for next iteration. */
      SVN_ERR(svn_io_file_get_offset(&pos, apr_file, iterpool));

      if (in_blob)
        {
          char c = line->data[0];

          /* 66 = len byte + (52/4*5) chars */
          if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
              && line->len <= 66
              && !strchr(line->data, ':')
              && !strchr(line->data, ' '))
            {
              /* One more blop line */
              if (in_src)
                bpatch->src_end = pos;
              else
                bpatch->dst_end = pos;
            }
          else if (svn_stringbuf_first_non_whitespace(line) < line->len
                   && !(in_src && bpatch->src_start < last_line))
            {
              break; /* Bad patch */
            }
          else if (in_src)
            {
              patch->binary_patch = bpatch; /* SUCCESS! */
              break; 
            }
          else
            {
              in_blob = FALSE;
              in_src = TRUE;
            }
        }
      else if (starts_with(line->data, "literal "))
        {
          apr_uint64_t expanded_size;
          svn_error_t *err = svn_cstring_strtoui64(&expanded_size,
                                                   &line->data[8],
                                                   0, APR_UINT64_MAX, 10);

          if (err)
            {
              svn_error_clear(err);
              break;
            }

          if (in_src)
            {
              bpatch->src_start = pos;
              bpatch->src_filesize = expanded_size;
            }
          else
            {
              bpatch->dst_start = pos;
              bpatch->dst_filesize = expanded_size;
            }
          in_blob = TRUE;
        }
      else
        break; /* We don't support GIT deltas (yet) */
    }
  svn_pool_destroy(iterpool);

  if (!eof)
    /* Rewind to the start of the line just read, so subsequent calls
     * don't end up skipping the line. It may contain a patch or hunk header.*/
    SVN_ERR(svn_io_file_seek(apr_file, APR_SET, &last_line, scratch_pool));
  else if (in_src
           && ((bpatch->src_end > bpatch->src_start) || !bpatch->src_filesize))
    {
      patch->binary_patch = bpatch; /* SUCCESS */
    }

  /* Reverse patch if requested */
  if (reverse && patch->binary_patch)
    {
      apr_off_t tmp_start = bpatch->src_start;
      apr_off_t tmp_end = bpatch->src_end;
      svn_filesize_t tmp_filesize = bpatch->src_filesize;

      bpatch->src_start = bpatch->dst_start;
      bpatch->src_end = bpatch->dst_end;
      bpatch->src_filesize = bpatch->dst_filesize;

      bpatch->dst_start = tmp_start;
      bpatch->dst_end = tmp_end;
      bpatch->dst_filesize = tmp_filesize;
    }

  return SVN_NO_ERROR;
}