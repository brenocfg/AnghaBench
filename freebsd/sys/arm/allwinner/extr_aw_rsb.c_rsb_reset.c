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
struct rsb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int IIC_ENOADDR ; 
 int /*<<< orphan*/  RSB_CTRL ; 
 int /*<<< orphan*/  RSB_LOCK (struct rsb_softc*) ; 
 int RSB_READ (struct rsb_softc*,int /*<<< orphan*/ ) ; 
 int RSB_RESET_RETRY ; 
 int /*<<< orphan*/  RSB_UNLOCK (struct rsb_softc*) ; 
 int /*<<< orphan*/  RSB_WRITE (struct rsb_softc*,int /*<<< orphan*/ ,int) ; 
 int SOFT_RESET ; 
 struct rsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
rsb_reset(device_t dev, u_char speed, u_char addr, u_char *oldaddr)
{
	struct rsb_softc *sc;
	int retry;

	sc = device_get_softc(dev);

	RSB_LOCK(sc);

	/* Write soft-reset bit and wait for it to self-clear. */
	RSB_WRITE(sc, RSB_CTRL, SOFT_RESET);
	for (retry = RSB_RESET_RETRY; retry > 0; retry--)
		if ((RSB_READ(sc, RSB_CTRL) & SOFT_RESET) == 0)
			break;

	RSB_UNLOCK(sc);

	if (retry == 0) {
		device_printf(dev, "soft reset timeout\n");
		return (ETIMEDOUT);
	}

	return (IIC_ENOADDR);
}