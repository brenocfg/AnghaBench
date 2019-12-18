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
struct TYPE_3__ {int /*<<< orphan*/ * state_pool; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */

__attribute__((used)) static apr_pool_t *
xes_pool(const svn_ra_serf__xml_estate_t *xes)
{
  /* Move up through parent states looking for one with a pool. This
     will always terminate since the initial state has a pool.  */
  while (xes->state_pool == NULL)
    xes = xes->prev;
  return xes->state_pool;
}