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
struct bwn_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  bwn_stop (struct bwn_softc*) ; 
 struct bwn_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_suspend(device_t dev)
{
	struct bwn_softc *sc = device_get_softc(dev);

	BWN_LOCK(sc);
	bwn_stop(sc);
	BWN_UNLOCK(sc);
	return (0);
}