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
struct TYPE_2__ {scalar_t__ dramtype; scalar_t__ eccen; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 TYPE_1__* drp0 ; 
 int /*<<< orphan*/  pnd2_printk (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int check_channel(int ch)
{
	if (drp0[ch].dramtype != 0) {
		pnd2_printk(KERN_INFO, "Unsupported DIMM in channel %d\n", ch);
		return 1;
	} else if (drp0[ch].eccen == 0) {
		pnd2_printk(KERN_INFO, "ECC disabled on channel %d\n", ch);
		return 1;
	}
	return 0;
}