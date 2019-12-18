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
struct ida_softc {int dummy; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  R_42XX_REPLY ; 
 int ida_inl (struct ida_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_outl (struct ida_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bus_addr_t
ida_v4_done(struct ida_softc *ida)
{
	bus_addr_t completed;

	completed = ida_inl(ida, R_42XX_REPLY);
	if (completed == -1)
		return (0);			/* fifo is empty */
	ida_outl(ida, R_42XX_REPLY, 0);		/* confirm read */
	return (completed);
}