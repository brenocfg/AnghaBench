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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * SVN_WC__ADM_ENTRIES ; 
 int /*<<< orphan*/ * SVN_WC__ADM_FORMAT ; 
 int /*<<< orphan*/  SVN_WC__ADM_PRISTINE ; 
 int /*<<< orphan*/  SVN_WC__NON_ENTRIES_STRING ; 
 int /*<<< orphan*/  init_adm_tmp_area (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_adm_subdir (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make_hidden (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__adm_child (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_init (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
init_adm(svn_wc__db_t *db,
         const char *local_abspath,
         const char *repos_relpath,
         const char *repos_root_url,
         const char *repos_uuid,
         svn_revnum_t initial_rev,
         svn_depth_t depth,
         apr_pool_t *pool)
{
  /* First, make an empty administrative area. */
  SVN_ERR(svn_io_dir_make_hidden(svn_wc__adm_child(local_abspath, NULL, pool),
                                 APR_OS_DEFAULT, pool));

  /** Make subdirectories. ***/

  /* SVN_WC__ADM_PRISTINE */
  SVN_ERR(make_adm_subdir(local_abspath, SVN_WC__ADM_PRISTINE, pool));

  /* ### want to add another directory? do a format bump to ensure that
     ### all existing working copies get the new directories. or maybe
     ### create-on-demand (more expensive)  */

  /** Init the tmp area. ***/
  SVN_ERR(init_adm_tmp_area(local_abspath, pool));

  /* Create the SDB. */
  SVN_ERR(svn_wc__db_init(db, local_abspath,
                          repos_relpath, repos_root_url, repos_uuid,
                          initial_rev, depth,
                          pool));

  /* Stamp ENTRIES and FORMAT files for old clients.  */
  SVN_ERR(svn_io_file_create(svn_wc__adm_child(local_abspath,
                                               SVN_WC__ADM_ENTRIES,
                                               pool),
                             SVN_WC__NON_ENTRIES_STRING,
                             pool));
  SVN_ERR(svn_io_file_create(svn_wc__adm_child(local_abspath,
                                               SVN_WC__ADM_FORMAT,
                                               pool),
                             SVN_WC__NON_ENTRIES_STRING,
                             pool));

  return SVN_NO_ERROR;
}