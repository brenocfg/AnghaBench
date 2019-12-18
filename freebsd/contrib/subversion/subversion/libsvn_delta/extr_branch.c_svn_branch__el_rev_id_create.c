#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
struct TYPE_4__ {int eid; int /*<<< orphan*/  rev; int /*<<< orphan*/ * branch; } ;
typedef  TYPE_1__ svn_branch__el_rev_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_branch__el_rev_id_t *
svn_branch__el_rev_id_create(svn_branch__state_t *branch,
                             int eid,
                             svn_revnum_t rev,
                             apr_pool_t *result_pool)
{
  svn_branch__el_rev_id_t *id = apr_palloc(result_pool, sizeof(*id));

  id->branch = branch;
  id->eid = eid;
  id->rev = rev;
  return id;
}