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
struct ipw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_LOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_UNLOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_stop_locked (struct ipw_softc*) ; 

__attribute__((used)) static void
ipw_stop(void *priv)
{
	struct ipw_softc *sc = priv;

	IPW_LOCK(sc);
	ipw_stop_locked(sc);
	IPW_UNLOCK(sc);
}