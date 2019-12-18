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
struct emu_sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  emumix_set_gpr (struct emu_sc_info*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log2lin (int /*<<< orphan*/ ) ; 

void
emumix_set_fxvol(struct emu_sc_info *sc, unsigned gpr, int32_t vol)
{

	vol = log2lin(vol);
	emumix_set_gpr(sc, gpr, vol);
}