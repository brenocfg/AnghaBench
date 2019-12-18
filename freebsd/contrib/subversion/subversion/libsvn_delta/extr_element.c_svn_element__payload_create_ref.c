#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {int eid; int /*<<< orphan*/  branch_id; int /*<<< orphan*/  rev; } ;
struct TYPE_7__ {TYPE_1__ branch_ref; int /*<<< orphan*/  kind; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ svn_element__payload_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_element__payload_invariants (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 

svn_element__payload_t *
svn_element__payload_create_ref(svn_revnum_t rev,
                                const char *branch_id,
                                int eid,
                                apr_pool_t *result_pool)
{
  svn_element__payload_t *new_payload
    = apr_pcalloc(result_pool, sizeof(*new_payload));

  new_payload->pool = result_pool;
  new_payload->kind = svn_node_unknown;
  new_payload->branch_ref.rev = rev;
  new_payload->branch_ref.branch_id = apr_pstrdup(result_pool, branch_id);
  new_payload->branch_ref.eid = eid;
  assert(svn_element__payload_invariants(new_payload));
  return new_payload;
}