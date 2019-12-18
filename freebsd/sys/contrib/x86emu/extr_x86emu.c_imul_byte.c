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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int R_AL; int R_AH; int /*<<< orphan*/  R_AX; } ;
struct x86emu {TYPE_1__ x86; } ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
imul_byte(struct x86emu *emu, uint8_t s)
{
	int16_t res = (int16_t) ((int8_t) emu->x86.R_AL * (int8_t) s);

	emu->x86.R_AX = res;
	if (((emu->x86.R_AL & 0x80) == 0 && emu->x86.R_AH == 0x00) ||
	    ((emu->x86.R_AL & 0x80) != 0 && emu->x86.R_AH == 0xFF)) {
		CLEAR_FLAG(F_CF);
		CLEAR_FLAG(F_OF);
	} else {
		SET_FLAG(F_CF);
		SET_FLAG(F_OF);
	}
}