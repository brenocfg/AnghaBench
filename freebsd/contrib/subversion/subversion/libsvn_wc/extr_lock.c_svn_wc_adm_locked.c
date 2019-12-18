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
struct TYPE_3__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_wclock_owns_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_boolean_t
svn_wc_adm_locked(const svn_wc_adm_access_t *adm_access)
{
  svn_boolean_t locked;
  apr_pool_t *subpool = svn_pool_create(adm_access->pool);
  svn_error_t *err = svn_wc__db_wclock_owns_lock(&locked, adm_access->db,
                                                 adm_access->abspath, TRUE,
                                                 subpool);
  svn_pool_destroy(subpool);

  if (err)
    {
      svn_error_clear(err);
      /* ### is this right? */
      return FALSE;
    }

  return locked;
}