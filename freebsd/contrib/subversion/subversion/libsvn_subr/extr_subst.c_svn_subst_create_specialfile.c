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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct special_stream_baton {int /*<<< orphan*/  write_content; int /*<<< orphan*/  write_stream; int /*<<< orphan*/ * pool; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct special_stream_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  close_handler_special ; 
 int /*<<< orphan*/ * svn_stream_create (struct special_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_stringbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_handler_special ; 

svn_error_t *
svn_subst_create_specialfile(svn_stream_t **stream,
                             const char *path,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  struct special_stream_baton *baton = apr_palloc(result_pool, sizeof(*baton));

  baton->path = apr_pstrdup(result_pool, path);

  /* SCRATCH_POOL may not exist after the function returns. */
  baton->pool = result_pool;

  baton->write_content = svn_stringbuf_create_empty(result_pool);
  baton->write_stream = svn_stream_from_stringbuf(baton->write_content,
                                                  result_pool);

  *stream = svn_stream_create(baton, result_pool);
  svn_stream_set_write(*stream, write_handler_special);
  svn_stream_set_close(*stream, close_handler_special);

  return SVN_NO_ERROR;
}