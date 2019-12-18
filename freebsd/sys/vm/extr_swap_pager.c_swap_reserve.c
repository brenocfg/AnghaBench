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
typedef  int /*<<< orphan*/  vm_ooffset_t ;
struct TYPE_2__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 TYPE_1__* curthread ; 
 int swap_reserve_by_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
swap_reserve(vm_ooffset_t incr)
{

	return (swap_reserve_by_cred(incr, curthread->td_ucred));
}