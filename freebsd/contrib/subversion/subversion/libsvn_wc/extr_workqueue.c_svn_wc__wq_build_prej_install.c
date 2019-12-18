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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* OP_PREJ_INSTALL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_to_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__wq_build_prej_install(svn_skel_t **work_item,
                              svn_wc__db_t *db,
                              const char *local_abspath,
                              /*svn_skel_t *conflict_skel,*/
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  const char *local_relpath;
  *work_item = svn_skel__make_empty_list(result_pool);

  SVN_ERR(svn_wc__db_to_relpath(&local_relpath, db, local_abspath,
                                local_abspath, result_pool, scratch_pool));

  /* ### In Subversion 1.7 and 1.8 we created a legacy property conflict skel
         here:
    if (conflict_skel != NULL)
      svn_skel__prepend(conflict_skel, *work_item);
   */
  svn_skel__prepend_str(local_relpath, *work_item, result_pool);
  svn_skel__prepend_str(OP_PREJ_INSTALL, *work_item, result_pool);

  return SVN_NO_ERROR;
}