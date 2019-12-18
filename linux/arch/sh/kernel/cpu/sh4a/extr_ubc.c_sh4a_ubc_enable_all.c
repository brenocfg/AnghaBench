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
struct TYPE_2__ {int num_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBC_CBR (int) ; 
 int UBC_CBR_CE ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ sh4a_ubc ; 

__attribute__((used)) static void sh4a_ubc_enable_all(unsigned long mask)
{
	int i;

	for (i = 0; i < sh4a_ubc.num_events; i++)
		if (mask & (1 << i))
			__raw_writel(__raw_readl(UBC_CBR(i)) | UBC_CBR_CE,
				     UBC_CBR(i));
}