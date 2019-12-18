#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ IS_MISSING (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__db_temp_close_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc__db_temp_get_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_set_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_to_shared(svn_wc_adm_access_t *lock, apr_pool_t *scratch_pool)
{
  /* ### sometimes we replace &missing with a now-valid lock.  */
  {
    svn_wc_adm_access_t *prior = svn_wc__db_temp_get_access(lock->db,
                                                            lock->abspath,
                                                            scratch_pool);
    if (IS_MISSING(prior))
      SVN_ERR(svn_wc__db_temp_close_access(lock->db, lock->abspath,
                                           prior, scratch_pool));
  }

  svn_wc__db_temp_set_access(lock->db, lock->abspath, lock,
                             scratch_pool);

  return SVN_NO_ERROR;
}