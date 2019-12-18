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
struct TYPE_2__ {unsigned long limit; unsigned long start; } ;

/* Variables and functions */
 TYPE_1__* tlbcam_addrs ; 

unsigned long tlbcam_sz(int idx)
{
	return tlbcam_addrs[idx].limit - tlbcam_addrs[idx].start + 1;
}