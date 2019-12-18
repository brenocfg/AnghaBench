#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct special_stream_baton {int /*<<< orphan*/  write_content; int /*<<< orphan*/  write_stream; int /*<<< orphan*/ * read_stream; int /*<<< orphan*/  path; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 struct special_stream_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  close_handler_special ; 
 int /*<<< orphan*/  read_handler_special ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_stream_create (struct special_stream_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_from_stringbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_subst_read_specialfile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_handler_special ; 

svn_error_t *
svn_subst_stream_from_specialfile(svn_stream_t **stream,
                                  const char *path,
                                  apr_pool_t *pool)
{
  struct special_stream_baton *baton = apr_palloc(pool, sizeof(*baton));
  svn_error_t *err;

  baton->pool = pool;
  baton->path = apr_pstrdup(pool, path);

  err = svn_subst_read_specialfile(&baton->read_stream, path, pool, pool);

  /* File might not exist because we intend to create it upon close. */
  if (err && APR_STATUS_IS_ENOENT(err->apr_err))
    {
      svn_error_clear(err);

      /* Note: the special file is missing. the caller won't find out
         until the first read. Oh well. This function is deprecated anyways,
         so they can just deal with the weird behavior. */
      baton->read_stream = NULL;
    }

  baton->write_content = svn_stringbuf_create_empty(pool);
  baton->write_stream = svn_stream_from_stringbuf(baton->write_content, pool);

  *stream = svn_stream_create(baton, pool);
  svn_stream_set_read2(*stream, NULL /* only full read support */,
                       read_handler_special);
  svn_stream_set_write(*stream, write_handler_special);
  svn_stream_set_close(*stream, close_handler_special);

  return SVN_NO_ERROR;
}