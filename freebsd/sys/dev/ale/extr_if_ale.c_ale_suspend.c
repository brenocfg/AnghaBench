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
struct ale_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_LOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_UNLOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_setwol (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_stop (struct ale_softc*) ; 
 struct ale_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ale_suspend(device_t dev)
{
	struct ale_softc *sc;

	sc = device_get_softc(dev);

	ALE_LOCK(sc);
	ale_stop(sc);
	ale_setwol(sc);
	ALE_UNLOCK(sc);

	return (0);
}