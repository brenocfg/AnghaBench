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
struct TYPE_3__ {int is_dor; } ;
typedef  TYPE_1__ osm_ucast_mgr_t ;

/* Variables and functions */
 int ucast_mgr_build_lfts (TYPE_1__*) ; 

__attribute__((used)) static int ucast_dor_build_lfts(void *context)
{
	osm_ucast_mgr_t *mgr = context;
	int ret;

	mgr->is_dor = 1;
	ret = ucast_mgr_build_lfts(mgr);
	mgr->is_dor = 0;

	return ret;
}