#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {char* data; int len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_17__ {int /*<<< orphan*/ * mergeinfo; int /*<<< orphan*/ * reverse_mergeinfo; scalar_t__ reverse; } ;
typedef  TYPE_2__ svn_patch_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
struct TYPE_18__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct TYPE_19__ {scalar_t__ original_length; scalar_t__ modified_length; } ;
typedef  TYPE_4__ svn_diff_hunk_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 scalar_t__ SVN_ERR_MERGEINFO_PARSE_ERROR ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ svn_ctype_isspace (char) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_mergeinfo_merge2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_mergeinfo_parse (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,char) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_mergeinfo(svn_boolean_t *found_mergeinfo,
                svn_stringbuf_t *line,
                svn_diff_hunk_t *hunk,
                svn_patch_t *patch,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  char *slash = strchr(line->data, '/');
  char *colon = strrchr(line->data, ':');

  *found_mergeinfo = FALSE;

  if (slash && colon && colon[1] == 'r' && slash < colon)
    {
      svn_stringbuf_t *input;
      svn_mergeinfo_t mergeinfo = NULL;
      char *s;
      svn_error_t *err;

      input = svn_stringbuf_create_ensure(line->len, scratch_pool);

      /* Copy the merge source path + colon */
      s = slash;
      while (s <= colon)
        {
          svn_stringbuf_appendbyte(input, *s);
          s++;
        }

      /* skip 'r' after colon */
      s++;

      /* Copy the revision range. */
      while (s < line->data + line->len)
        {
          if (svn_ctype_isspace(*s))
            break;
          svn_stringbuf_appendbyte(input, *s);
          s++;
        }

      err = svn_mergeinfo_parse(&mergeinfo, input->data, result_pool);
      if (err && err->apr_err == SVN_ERR_MERGEINFO_PARSE_ERROR)
        {
          svn_error_clear(err);
          mergeinfo = NULL;
        }
      else
        SVN_ERR(err);

      if (mergeinfo)
        {
          if (hunk->original_length > 0) /* reverse merges */
            {
              if (patch->reverse)
                {
                  if (patch->mergeinfo == NULL)
                    patch->mergeinfo = mergeinfo;
                  else
                    SVN_ERR(svn_mergeinfo_merge2(patch->mergeinfo,
                                                 mergeinfo,
                                                 result_pool,
                                                 scratch_pool));
                }
              else
                {
                  if (patch->reverse_mergeinfo == NULL)
                    patch->reverse_mergeinfo = mergeinfo;
                  else
                    SVN_ERR(svn_mergeinfo_merge2(patch->reverse_mergeinfo,
                                                 mergeinfo,
                                                 result_pool,
                                                 scratch_pool));
                }
              hunk->original_length--;
            }
          else if (hunk->modified_length > 0) /* forward merges */
            {
              if (patch->reverse)
                {
                  if (patch->reverse_mergeinfo == NULL)
                    patch->reverse_mergeinfo = mergeinfo;
                  else
                    SVN_ERR(svn_mergeinfo_merge2(patch->reverse_mergeinfo,
                                                 mergeinfo,
                                                 result_pool,
                                                 scratch_pool));
                }
              else
                {
                  if (patch->mergeinfo == NULL)
                    patch->mergeinfo = mergeinfo;
                  else
                    SVN_ERR(svn_mergeinfo_merge2(patch->mergeinfo,
                                                 mergeinfo,
                                                 result_pool,
                                                 scratch_pool));
                }
              hunk->modified_length--;
            }

          *found_mergeinfo = TRUE;
        }
    }

  return SVN_NO_ERROR;
}