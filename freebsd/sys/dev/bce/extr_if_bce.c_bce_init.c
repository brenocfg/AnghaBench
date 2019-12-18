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
struct bce_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_LOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_UNLOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_init_locked (struct bce_softc*) ; 

__attribute__((used)) static void
bce_init(void *xsc)
{
	struct bce_softc *sc = xsc;

	DBENTER(BCE_VERBOSE_RESET);

	BCE_LOCK(sc);
	bce_init_locked(sc);
	BCE_UNLOCK(sc);

	DBEXIT(BCE_VERBOSE_RESET);
}