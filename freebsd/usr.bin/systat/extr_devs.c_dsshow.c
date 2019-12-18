#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct statinfo {int dummy; } ;
struct TYPE_2__ {scalar_t__ selected; } ;

/* Variables and functions */
 TYPE_1__* dev_select ; 
 int /*<<< orphan*/  dsshow3 (int,int,int,int,struct statinfo*,struct statinfo*) ; 
 int num_devices ; 

void
dsshow(int maxdrives, int diskcol, int diskrow, struct statinfo *now, struct statinfo *then)
{
	int i, lc;

	for (i = 0, lc = 0; i < num_devices && lc < maxdrives; i++)
		if (dev_select[i].selected)
			dsshow3(diskcol, diskrow, i, ++lc, now, then);
}