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
typedef  scalar_t__ PVBUS_EXT ;

/* Variables and functions */
 int /*<<< orphan*/  __hpt_do_tasks (scalar_t__) ; 
 int /*<<< orphan*/  hpt_lock_vbus (scalar_t__) ; 
 int /*<<< orphan*/  hpt_unlock_vbus (scalar_t__) ; 

__attribute__((used)) static void hpt_do_tasks(PVBUS_EXT vbus_ext, int pending)
{
	if(vbus_ext){
		hpt_lock_vbus(vbus_ext);
		__hpt_do_tasks(vbus_ext);
		hpt_unlock_vbus(vbus_ext);
	}
}