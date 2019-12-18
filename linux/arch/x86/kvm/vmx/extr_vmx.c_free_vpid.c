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

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_vpid ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmx_vpid_bitmap ; 
 int /*<<< orphan*/  vmx_vpid_lock ; 

void free_vpid(int vpid)
{
	if (!enable_vpid || vpid == 0)
		return;
	spin_lock(&vmx_vpid_lock);
	__clear_bit(vpid, vmx_vpid_bitmap);
	spin_unlock(&vmx_vpid_lock);
}