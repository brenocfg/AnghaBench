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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int intr; int /*<<< orphan*/  intno; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int INTR_SYNCH ; 
 int /*<<< orphan*/  x86emu_intr_dispatch (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
x86emu_intr_handle(struct x86emu *emu)
{
	uint8_t intno;

	if (emu->x86.intr & INTR_SYNCH) {
		intno = emu->x86.intno;
		emu->x86.intr = 0;
		x86emu_intr_dispatch(emu, intno);
	}
}