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
typedef  int /*<<< orphan*/  svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_stat_dirent2 (int /*<<< orphan*/  const**,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
stat_wc_dirent_case_sensitive(const svn_io_dirent2_t **dirent,
                              svn_wc__db_t *db,
                              const char *local_abspath,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  svn_boolean_t is_wcroot;

  /* The wcroot is "" inside the wc; handle it as not in the wc, as
     the case of the root is indifferent to us. */

  /* Note that for performance this is really just a few hashtable lookups,
     as we just used local_abspath for a db call in both our callers */
  SVN_ERR(svn_wc__db_is_wcroot(&is_wcroot, db, local_abspath,
                               scratch_pool));

  return svn_error_trace(
            svn_io_stat_dirent2(dirent, local_abspath,
                                ! is_wcroot /* verify_truename */,
                                TRUE        /* ignore_enoent */,
                                result_pool, scratch_pool));
}