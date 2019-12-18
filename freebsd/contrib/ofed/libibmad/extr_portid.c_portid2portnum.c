#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cnt; int* p; } ;
struct TYPE_5__ {scalar_t__ lid; TYPE_1__ drpath; } ;
typedef  TYPE_2__ ib_portid_t ;

/* Variables and functions */

int portid2portnum(ib_portid_t * portid)
{
	if (portid->lid > 0)
		return -1;

	if (portid->drpath.cnt == 0)
		return 0;

	return portid->drpath.p[(portid->drpath.cnt - 1)];
}