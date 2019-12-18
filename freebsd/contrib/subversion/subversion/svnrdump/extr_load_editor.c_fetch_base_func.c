#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct revision_baton {TYPE_1__* pb; scalar_t__ rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  aux_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 TYPE_2__* svn_ra_get_file (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_unique (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fetch_base_func(const char **filename,
                void *baton,
                const char *path,
                svn_revnum_t base_revision,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  struct revision_baton *rb = baton;
  svn_stream_t *fstream;
  svn_error_t *err;

  if (! SVN_IS_VALID_REVNUM(base_revision))
    base_revision = rb->rev - 1;

  SVN_ERR(svn_stream_open_unique(&fstream, filename, NULL,
                                 svn_io_file_del_on_pool_cleanup,
                                 result_pool, scratch_pool));

  err = svn_ra_get_file(rb->pb->aux_session, path, base_revision,
                        fstream, NULL, NULL, scratch_pool);
  if (err && err->apr_err == SVN_ERR_FS_NOT_FOUND)
    {
      svn_error_clear(err);
      SVN_ERR(svn_stream_close(fstream));

      *filename = NULL;
      return SVN_NO_ERROR;
    }
  else if (err)
    return svn_error_trace(err);

  SVN_ERR(svn_stream_close(fstream));

  return SVN_NO_ERROR;
}