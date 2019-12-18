#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRISTINE_TEMPDIR_RELPATH ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* svn_dirent_join_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc_get_adm_dir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
pristine_get_tempdir(svn_wc__db_wcroot_t *wcroot,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  return svn_dirent_join_many(result_pool, wcroot->abspath,
                              svn_wc_get_adm_dir(scratch_pool),
                              PRISTINE_TEMPDIR_RELPATH, SVN_VA_NULL);
}