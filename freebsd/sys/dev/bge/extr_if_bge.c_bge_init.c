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
struct bge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_init_locked (struct bge_softc*) ; 

__attribute__((used)) static void
bge_init(void *xsc)
{
	struct bge_softc *sc = xsc;

	BGE_LOCK(sc);
	bge_init_locked(sc);
	BGE_UNLOCK(sc);
}