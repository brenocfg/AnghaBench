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
struct sfxge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_UNLOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_start (struct sfxge_softc*) ; 

__attribute__((used)) static void
sfxge_if_init(void *arg)
{
	struct sfxge_softc *sc;

	sc = (struct sfxge_softc *)arg;

	SFXGE_ADAPTER_LOCK(sc);
	(void)sfxge_start(sc);
	SFXGE_ADAPTER_UNLOCK(sc);
}