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
struct my_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MY_LOCK (struct my_softc*) ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 int /*<<< orphan*/  my_init_locked (struct my_softc*) ; 

__attribute__((used)) static void
my_init(void *xsc)
{
	struct my_softc *sc = xsc;

	MY_LOCK(sc);
	my_init_locked(sc);
	MY_UNLOCK(sc);
}