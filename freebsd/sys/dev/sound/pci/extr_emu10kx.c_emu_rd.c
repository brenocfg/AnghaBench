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
struct emu_sc_info {int dummy; } ;

/* Variables and functions */
 unsigned int EMU_DATA ; 
 unsigned int EMU_DATA2 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  emu_rd_nolock (struct emu_sc_info*,unsigned int,unsigned int) ; 

uint32_t
emu_rd(struct emu_sc_info *sc, unsigned int regno, unsigned int size)
{
	uint32_t rd;

	KASSERT(regno != EMU_DATA, ("emu_rd: attempt to read DATA"));
	KASSERT(regno != EMU_DATA2, ("emu_rd: attempt to read DATA2"));

	rd = emu_rd_nolock(sc, regno, size);
	return (rd);
}