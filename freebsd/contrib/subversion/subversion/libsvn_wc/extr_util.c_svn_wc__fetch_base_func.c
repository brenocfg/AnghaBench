#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct svn_wc__shim_fetch_baton_t {int /*<<< orphan*/  db; int /*<<< orphan*/  base_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_path (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__fetch_base_func(const char **filename,
                        void *baton,
                        const char *path,
                        svn_revnum_t base_revision,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  struct svn_wc__shim_fetch_baton_t *sfb = baton;
  const svn_checksum_t *checksum;
  svn_error_t *err;
  const char *local_abspath = svn_dirent_join(sfb->base_abspath, path,
                                              scratch_pool);

  err = svn_wc__db_base_get_info(NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, &checksum,
                                 NULL, NULL, NULL, NULL, NULL,
                                 sfb->db, local_abspath,
                                 scratch_pool, scratch_pool);
  if (err && err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
    {
      svn_error_clear(err);
      *filename = NULL;
      return SVN_NO_ERROR;
    }
  else if (err)
    return svn_error_trace(err);

  if (checksum == NULL)
    {
      *filename = NULL;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_wc__db_pristine_get_path(filename, sfb->db, local_abspath,
                                       checksum, scratch_pool, scratch_pool));

  return SVN_NO_ERROR;
}