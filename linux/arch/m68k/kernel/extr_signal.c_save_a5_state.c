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
struct switch_stack {int /*<<< orphan*/  a5; } ;
struct sigcontext {int /*<<< orphan*/  sc_a5; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void save_a5_state(struct sigcontext *sc, struct pt_regs *regs)
{
	sc->sc_a5 = ((struct switch_stack *)regs - 1)->a5;
}