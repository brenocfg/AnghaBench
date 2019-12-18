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
struct rt_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_init_locked (struct rt_softc*) ; 

__attribute__((used)) static void
rt_init(void *priv)
{
	struct rt_softc *sc;

	sc = priv;
	RT_SOFTC_LOCK(sc);
	rt_init_locked(sc);
	RT_SOFTC_UNLOCK(sc);
}