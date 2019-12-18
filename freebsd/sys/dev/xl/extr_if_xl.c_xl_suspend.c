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
struct xl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 struct xl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xl_setwol (struct xl_softc*) ; 
 int /*<<< orphan*/  xl_stop (struct xl_softc*) ; 

__attribute__((used)) static int
xl_suspend(device_t dev)
{
	struct xl_softc		*sc;

	sc = device_get_softc(dev);

	XL_LOCK(sc);
	xl_stop(sc);
	xl_setwol(sc);
	XL_UNLOCK(sc);

	return (0);
}