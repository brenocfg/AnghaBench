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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_AF ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int PARITY (int) ; 

__attribute__((used)) static uint16_t 
aam_word(struct x86emu *emu, uint8_t d)
{
	uint16_t h, l;

	h = (uint16_t) (d / 10);
	l = (uint16_t) (d % 10);
	l |= (uint16_t) (h << 8);

	CLEAR_FLAG(F_CF);
	CLEAR_FLAG(F_AF);
	CLEAR_FLAG(F_OF);
	CONDITIONAL_SET_FLAG(l & 0x80, F_SF);
	CONDITIONAL_SET_FLAG(l == 0, F_ZF);
	CONDITIONAL_SET_FLAG(PARITY(l & 0xff), F_PF);
	return l;
}