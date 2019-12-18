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
struct arge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_LOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  ARGE_UNLOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_update_link_locked (struct arge_softc*) ; 

__attribute__((used)) static void
arge_link_task(void *arg, int pending)
{
	struct arge_softc	*sc;
	sc = (struct arge_softc *)arg;

	ARGE_LOCK(sc);
	arge_update_link_locked(sc);
	ARGE_UNLOCK(sc);
}