#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* data; scalar_t__ len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_7__ {scalar_t__ base_length; scalar_t__ base_item_index; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  type; scalar_t__ header_size; } ;
typedef  TYPE_2__ svn_fs_fs__rep_header_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REP_DELTA ; 
 int /*<<< orphan*/  REP_PLAIN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_revnum (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char*) ; 
 char* svn_cstring_tokenize (char*,char**) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__rep_delta ; 
 int /*<<< orphan*/  svn_fs_fs__rep_plain ; 
 int /*<<< orphan*/  svn_fs_fs__rep_self_delta ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__read_rep_header(svn_fs_fs__rep_header_t **header,
                           svn_stream_t *stream,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *buffer;
  char *str, *last_str;
  apr_int64_t val;
  svn_boolean_t eol = FALSE;

  SVN_ERR(svn_stream_readline(stream, &buffer, "\n", &eol, scratch_pool));

  *header = apr_pcalloc(result_pool, sizeof(**header));
  (*header)->header_size = buffer->len + 1;
  if (strcmp(buffer->data, REP_PLAIN) == 0)
    {
      (*header)->type = svn_fs_fs__rep_plain;
      return SVN_NO_ERROR;
    }

  if (strcmp(buffer->data, REP_DELTA) == 0)
    {
      /* This is a delta against the empty stream. */
      (*header)->type = svn_fs_fs__rep_self_delta;
      return SVN_NO_ERROR;
    }

  (*header)->type = svn_fs_fs__rep_delta;

  /* We have hopefully a DELTA vs. a non-empty base revision. */
  last_str = buffer->data;
  str = svn_cstring_tokenize(" ", &last_str);
  if (! str || (strcmp(str, REP_DELTA) != 0))
    goto error;

  SVN_ERR(parse_revnum(&(*header)->base_revision, (const char **)&last_str));

  str = svn_cstring_tokenize(" ", &last_str);
  if (! str)
    goto error;
  SVN_ERR(svn_cstring_atoi64(&val, str));
  (*header)->base_item_index = (apr_off_t)val;

  str = svn_cstring_tokenize(" ", &last_str);
  if (! str)
    goto error;
  SVN_ERR(svn_cstring_atoi64(&val, str));
  (*header)->base_length = (svn_filesize_t)val;

  return SVN_NO_ERROR;

 error:
  return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                           _("Malformed representation header"));
}