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
struct nge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_init_locked (struct nge_softc*) ; 

__attribute__((used)) static void
nge_init(void *xsc)
{
	struct nge_softc *sc = xsc;

	NGE_LOCK(sc);
	nge_init_locked(sc);
	NGE_UNLOCK(sc);
}