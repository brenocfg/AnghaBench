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
struct TYPE_4__ {int /*<<< orphan*/ * state_pool; } ;
typedef  TYPE_1__ svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ensure_pool (TYPE_1__*) ; 

apr_pool_t *
svn_ra_serf__xml_state_pool(svn_ra_serf__xml_estate_t *xes)
{
  /* If they asked for a pool, then ensure that we have one to provide.  */
  ensure_pool(xes);

  return xes->state_pool;
}