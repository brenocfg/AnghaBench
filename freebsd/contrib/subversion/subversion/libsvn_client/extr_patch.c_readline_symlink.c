#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
struct symlink_baton_t {void* at_eof; int /*<<< orphan*/  local_abspath; } ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  svn_stringbuf_from_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_read_specialfile (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
readline_symlink(void *baton, svn_stringbuf_t **line, const char **eol_str,
                 svn_boolean_t *eof, apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  struct symlink_baton_t *sb = baton;

  if (eof)
    *eof = TRUE;
  if (eol_str)
    *eol_str = NULL;

  if (sb->at_eof)
    {
      *line = NULL;
    }
  else
    {
      svn_stream_t *stream;
      const apr_size_t len_hint = 64; /* arbitrary */

      SVN_ERR(svn_subst_read_specialfile(&stream, sb->local_abspath,
                                         scratch_pool, scratch_pool));
      SVN_ERR(svn_stringbuf_from_stream(line, stream, len_hint, result_pool));
      *eof = FALSE;
      sb->at_eof = TRUE;
    }

  return SVN_NO_ERROR;
}