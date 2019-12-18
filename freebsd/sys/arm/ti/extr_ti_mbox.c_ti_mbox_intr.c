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
struct ti_mbox_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,struct ti_mbox_softc*) ; 

__attribute__((used)) static void
ti_mbox_intr(void *arg)
{
	struct ti_mbox_softc *sc;

	sc = arg;
	DPRINTF("interrupt %p", sc);
}