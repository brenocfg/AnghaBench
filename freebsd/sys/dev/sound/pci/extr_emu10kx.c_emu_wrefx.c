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
struct emu_sc_info {scalar_t__ code_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  emu_wrptr (struct emu_sc_info*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static void
emu_wrefx(struct emu_sc_info *sc, unsigned int pc, unsigned int data)
{
	emu_wrptr(sc, 0, sc->code_base + pc, data);
}