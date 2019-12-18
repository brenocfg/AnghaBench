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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_stop (struct bge_softc*) ; 
 struct bge_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_suspend(device_t dev)
{
	struct bge_softc *sc;

	sc = device_get_softc(dev);
	BGE_LOCK(sc);
	bge_stop(sc);
	BGE_UNLOCK(sc);

	return (0);
}