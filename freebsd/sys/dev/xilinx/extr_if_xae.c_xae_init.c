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
struct xae_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XAE_LOCK (struct xae_softc*) ; 
 int /*<<< orphan*/  XAE_UNLOCK (struct xae_softc*) ; 
 int /*<<< orphan*/  xae_init_locked (struct xae_softc*) ; 

__attribute__((used)) static void
xae_init(void *arg)
{
	struct xae_softc *sc;

	sc = arg;

	XAE_LOCK(sc);
	xae_init_locked(sc);
	XAE_UNLOCK(sc);
}