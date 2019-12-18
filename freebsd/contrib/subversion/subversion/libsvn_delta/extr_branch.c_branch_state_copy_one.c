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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_element__payload_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
typedef  int /*<<< orphan*/  svn_branch__rev_bid_eid_t ;
typedef  int /*<<< orphan*/  svn_branch__eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
branch_state_copy_one(svn_branch__state_t *branch,
                      const svn_branch__rev_bid_eid_t *src_el_rev,
                      svn_branch__eid_t eid,
                      svn_branch__eid_t new_parent_eid,
                      const char *new_name,
                      const svn_element__payload_t *new_payload,
                      apr_pool_t *scratch_pool)
{
  /* New payload shall be the same as the source if NEW_PAYLOAD is null. */
  /* ### if (! new_payload)
    {
      new_payload = branch_map_get(branch, eid)->payload;
    }
   */

  return SVN_NO_ERROR;
}