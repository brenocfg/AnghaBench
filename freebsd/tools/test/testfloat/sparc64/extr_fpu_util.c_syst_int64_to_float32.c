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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */
 int /*<<< orphan*/  __fpu_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fpu_setreg64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emul_trap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insn_int64_to_float32 ; 

float32
syst_int64_to_float32(int64 a)
{

	__fpu_setreg64(0, a);
	emul_trap(&insn_int64_to_float32, 0x1UL);
	return (__fpu_getreg(0));
}