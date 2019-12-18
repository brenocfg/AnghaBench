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
struct TYPE_2__ {int addr; int eax; int edx; int ebx; int ecx; int /*<<< orphan*/  efl; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int EDD_INTERFACE_FIXED_DISK ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static int
bd_check_extensions(int unit)
{
	/* do not use ext calls for floppy devices */
	if (unit < 0x80)
		return (0);

	/* Determine if we can use EDD with this device. */
	v86.ctl = V86_FLAGS;
	v86.addr = 0x13;
	v86.eax = 0x4100;
	v86.edx = unit;
	v86.ebx = 0x55aa;
	v86int();

	if (V86_CY(v86.efl) ||			/* carry set */
	    (v86.ebx & 0xffff) != 0xaa55)	/* signature */
		return (0);

	/* extended disk access functions (AH=42h-44h,47h,48h) supported */
	if ((v86.ecx & EDD_INTERFACE_FIXED_DISK) == 0)
		return (0);

	return ((v86.eax >> 8) & 0xff);
}