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
 int KEYBUFSZ ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 int /*<<< orphan*/  V86_ZR (int /*<<< orphan*/ ) ; 
 scalar_t__* keybuf ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static int
vidc_ischar(void)
{
	int i;

	for (i = 0; i < KEYBUFSZ; i++) {
		if (keybuf[i] != 0) {
			return (1);
		}
	}

	v86.ctl = V86_FLAGS;
	v86.addr = 0x16;
	v86.eax = 0x100;
	v86int();
	return (!V86_ZR(v86.efl));
}