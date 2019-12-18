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
struct nfe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFE_LOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_UNLOCK (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_init_locked (struct nfe_softc*) ; 

__attribute__((used)) static void
nfe_init(void *xsc)
{
	struct nfe_softc *sc = xsc;

	NFE_LOCK(sc);
	nfe_init_locked(sc);
	NFE_UNLOCK(sc);
}