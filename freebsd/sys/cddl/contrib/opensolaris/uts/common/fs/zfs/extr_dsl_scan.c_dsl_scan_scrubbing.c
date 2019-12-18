#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ scn_state; scalar_t__ scn_func; } ;
typedef  TYPE_2__ dsl_scan_phys_t ;
struct TYPE_7__ {TYPE_1__* dp_scan; } ;
typedef  TYPE_3__ dsl_pool_t ;
typedef  int boolean_t ;
struct TYPE_5__ {TYPE_2__ scn_phys; } ;

/* Variables and functions */
 scalar_t__ DSS_SCANNING ; 
 scalar_t__ POOL_SCAN_SCRUB ; 

boolean_t
dsl_scan_scrubbing(const dsl_pool_t *dp)
{
	dsl_scan_phys_t *scn_phys = &dp->dp_scan->scn_phys;

	return (scn_phys->scn_state == DSS_SCANNING &&
	    scn_phys->scn_func == POOL_SCAN_SCRUB);
}