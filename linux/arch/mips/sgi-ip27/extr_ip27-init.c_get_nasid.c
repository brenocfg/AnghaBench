#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int LOCAL_HUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NI_STATUS_REV_ID ; 
 int NSRI_NODEID_MASK ; 
 int NSRI_NODEID_SHFT ; 

nasid_t
get_nasid(void)
{
	return (nasid_t)((LOCAL_HUB_L(NI_STATUS_REV_ID) & NSRI_NODEID_MASK)
			 >> NSRI_NODEID_SHFT);
}