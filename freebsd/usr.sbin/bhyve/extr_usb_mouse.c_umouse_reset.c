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
struct umouse_softc {scalar_t__ newdata; } ;

/* Variables and functions */

__attribute__((used)) static int
umouse_reset(void *scarg)
{
	struct umouse_softc *sc;

	sc = scarg;

	sc->newdata = 0;

	return (0);
}