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
struct TYPE_2__ {int addr; int edx; scalar_t__ eax; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  V86_FLAGS ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static void
bd_reset_disk(int unit)
{
	/* reset disk */
	v86.ctl = V86_FLAGS;
	v86.addr = 0x13;
	v86.eax = 0;
	v86.edx = unit;
	v86int();
}