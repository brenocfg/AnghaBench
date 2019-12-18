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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_wc__db_temp_get_access (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_wc_adm_access_t *
get_from_shared(const char *abspath,
                svn_wc__db_t *db,
                apr_pool_t *scratch_pool)
{
  /* We closed the DB when it became empty. ABSPATH is not present.  */
  if (db == NULL)
    return NULL;
  return svn_wc__db_temp_get_access(db, abspath, scratch_pool);
}