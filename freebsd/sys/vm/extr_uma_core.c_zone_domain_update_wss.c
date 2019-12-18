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
typedef  TYPE_1__* uma_zone_domain_t ;
struct TYPE_3__ {scalar_t__ uzd_imax; scalar_t__ uzd_imin; long uzd_nitems; int uzd_wss; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 

__attribute__((used)) static void
zone_domain_update_wss(uma_zone_domain_t zdom)
{
	long wss;

	MPASS(zdom->uzd_imax >= zdom->uzd_imin);
	wss = zdom->uzd_imax - zdom->uzd_imin;
	zdom->uzd_imax = zdom->uzd_imin = zdom->uzd_nitems;
	zdom->uzd_wss = (4 * wss + zdom->uzd_wss) / 5;
}