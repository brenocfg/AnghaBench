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
struct dtsec_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  DTSEC_UNLOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_if_init_locked (struct dtsec_softc*) ; 

__attribute__((used)) static void
dtsec_if_init(void *data)
{
	struct dtsec_softc *sc;

	sc = data;

	DTSEC_LOCK(sc);
	dtsec_if_init_locked(sc);
	DTSEC_UNLOCK(sc);
}