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
struct ida_softc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDA_INTERRUPTS ; 
 int /*<<< orphan*/  INT_DISABLE_42XX ; 
 int /*<<< orphan*/  INT_ENABLE_42XX ; 
 int /*<<< orphan*/  R_42XX_INT_MASK ; 
 int /*<<< orphan*/  ida_outl (struct ida_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ida_v4_int_enable(struct ida_softc *ida, int enable)
{
	if (enable)
		ida->flags |= IDA_INTERRUPTS;
	else
		ida->flags &= ~IDA_INTERRUPTS;
	ida_outl(ida, R_42XX_INT_MASK,
	    enable ? INT_ENABLE_42XX : INT_DISABLE_42XX);
}