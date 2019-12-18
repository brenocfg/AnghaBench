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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct x86emu {int /*<<< orphan*/  (* emu_rdb ) (struct x86emu*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct x86emu*,int) ; 

__attribute__((used)) static uint8_t 
fetch_byte(struct x86emu *emu, uint32_t segment, uint32_t offset)
{
	return (*emu->emu_rdb) (emu, ((uint32_t) segment << 4) + offset);
}