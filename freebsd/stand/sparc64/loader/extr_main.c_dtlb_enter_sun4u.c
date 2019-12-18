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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int OF_call_method (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu ; 

__attribute__((used)) static int
dtlb_enter_sun4u(u_int index, u_long data, vm_offset_t virt)
{

	return (OF_call_method("SUNW,dtlb-load", mmu, 3, 0, index, data,
	    virt));
}