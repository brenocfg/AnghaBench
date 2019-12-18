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
struct arge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_LOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  ARGE_UNLOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_stop (struct arge_softc*) ; 
 struct arge_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arge_shutdown(device_t dev)
{
	struct arge_softc	*sc;

	sc = device_get_softc(dev);

	ARGE_LOCK(sc);
	arge_stop(sc);
	ARGE_UNLOCK(sc);

	return (0);
}