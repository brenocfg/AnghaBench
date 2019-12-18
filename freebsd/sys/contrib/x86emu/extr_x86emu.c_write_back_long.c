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
typedef  int /*<<< orphan*/  uint32_t ;
struct x86emu {int cur_mod; int /*<<< orphan*/  cur_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/ * decode_rl_long_register (struct x86emu*) ; 
 int /*<<< orphan*/  store_data_long (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_back_long(struct x86emu *emu, uint32_t val)
{
	if (emu->cur_mod != 3)
		store_data_long(emu, emu->cur_offset, val);
	else
		*decode_rl_long_register(emu) = val;
}