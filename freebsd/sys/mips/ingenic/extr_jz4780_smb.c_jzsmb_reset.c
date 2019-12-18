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
typedef  int /*<<< orphan*/  u_char ;
struct jzsmb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMB_LOCK (struct jzsmb_softc*) ; 
 int /*<<< orphan*/  SMB_UNLOCK (struct jzsmb_softc*) ; 
 struct jzsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int jzsmb_reset_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jzsmb_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct jzsmb_softc *sc;
	int error;

	sc = device_get_softc(dev);

	SMB_LOCK(sc);
	error = jzsmb_reset_locked(dev, addr);
	SMB_UNLOCK(sc);

	return (error);
}