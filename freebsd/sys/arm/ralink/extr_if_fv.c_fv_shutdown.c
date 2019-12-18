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
struct fv_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FV_LOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  FV_UNLOCK (struct fv_softc*) ; 
 struct fv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fv_stop (struct fv_softc*) ; 

__attribute__((used)) static int
fv_shutdown(device_t dev)
{
	struct fv_softc	*sc;

	sc = device_get_softc(dev);

	FV_LOCK(sc);
	fv_stop(sc);
	FV_UNLOCK(sc);

	return (0);
}