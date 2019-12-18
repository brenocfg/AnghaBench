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
struct TYPE_2__ {int addr; int eax; int /*<<< orphan*/  efl; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  V86_FLAGS ; 
 scalar_t__ V86_ZR (int /*<<< orphan*/ ) ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

int
getc(int fn)
{

	v86.ctl = V86_FLAGS;
	v86.addr = 0x16;
	v86.eax = fn << 8;
	v86int();

	if (fn == 0)
		return (v86.eax);

	if (V86_ZR(v86.efl))
		return (0);
	return (v86.eax);
}