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
struct TYPE_3__ {scalar_t__ es_fid; scalar_t__ es_untagged_ports; scalar_t__ es_member_ports; scalar_t__ es_vid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */

__attribute__((used)) static int
ukswitch_getvgroup(device_t dev, etherswitch_vlangroup_t *vg)
{

	/* Not supported. */
	vg->es_vid = 0;
	vg->es_member_ports = 0;
	vg->es_untagged_ports = 0;
	vg->es_fid = 0;
	return (0);
}