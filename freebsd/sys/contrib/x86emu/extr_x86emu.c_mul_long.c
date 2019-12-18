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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int R_EAX; int R_EDX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
mul_long(struct x86emu *emu, uint32_t s)
{
	uint64_t res = (uint64_t) emu->x86.R_EAX * s;

	emu->x86.R_EAX = (uint32_t) res;
	emu->x86.R_EDX = (uint32_t) (res >> 32);

	if (emu->x86.R_EDX == 0) {
		CLEAR_FLAG(F_CF);
		CLEAR_FLAG(F_OF);
	} else {
		SET_FLAG(F_CF);
		SET_FLAG(F_OF);
	}
}