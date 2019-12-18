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
struct rl_softc {int suspended; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RL_LOCK (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_UNLOCK (struct rl_softc*) ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_setwol (struct rl_softc*) ; 
 int /*<<< orphan*/  re_stop (struct rl_softc*) ; 

__attribute__((used)) static int
re_suspend(device_t dev)
{
	struct rl_softc		*sc;

	sc = device_get_softc(dev);

	RL_LOCK(sc);
	re_stop(sc);
	re_setwol(sc);
	sc->suspended = 1;
	RL_UNLOCK(sc);

	return (0);
}