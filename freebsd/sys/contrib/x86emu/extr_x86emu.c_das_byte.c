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
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_AF ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int PARITY (int) ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t 
das_byte(struct x86emu *emu, uint8_t d)
{
	if ((d & 0xf) > 9 || ACCESS_FLAG(F_AF)) {
		d -= 6;
		SET_FLAG(F_AF);
	}
	if (d > 0x9F || ACCESS_FLAG(F_CF)) {
		d -= 0x60;
		SET_FLAG(F_CF);
	}
	CONDITIONAL_SET_FLAG(d & 0x80, F_SF);
	CONDITIONAL_SET_FLAG(d == 0, F_ZF);
	CONDITIONAL_SET_FLAG(PARITY(d & 0xff), F_PF);
	return d;
}