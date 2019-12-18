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
struct TYPE_3__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_pool_cleanup_kill (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_cleanup_locked ; 
 int /*<<< orphan*/  pool_cleanup_readonly ; 

__attribute__((used)) static apr_status_t
pool_cleanup_child(void *p)
{
  svn_wc_adm_access_t *lock = p;

  apr_pool_cleanup_kill(lock->pool, lock, pool_cleanup_locked);
  apr_pool_cleanup_kill(lock->pool, lock, pool_cleanup_readonly);

  return APR_SUCCESS;
}