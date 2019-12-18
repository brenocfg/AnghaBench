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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct x86emu {int /*<<< orphan*/  (* emu_wrw ) (struct x86emu*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct x86emu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
store_word(struct x86emu *emu, uint32_t segment, uint32_t offset, uint16_t val)
{
	(*emu->emu_wrw) (emu, ((uint32_t) segment << 4) + offset, val);
}