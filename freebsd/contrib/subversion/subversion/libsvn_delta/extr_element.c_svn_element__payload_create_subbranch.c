#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  is_subbranch_root; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_element__payload_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_element__payload_invariants (TYPE_1__*) ; 

svn_element__payload_t *
svn_element__payload_create_subbranch(apr_pool_t *result_pool)
{
  svn_element__payload_t *new_payload
    = apr_pcalloc(result_pool, sizeof(*new_payload));

  new_payload->pool = result_pool;
  new_payload->is_subbranch_root = TRUE;
  assert(svn_element__payload_invariants(new_payload));
  return new_payload;
}