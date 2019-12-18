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
typedef  int /*<<< orphan*/  u_long ;
struct xbd_softc {int dummy; } ;
struct thread {int dummy; } ;
struct disk {struct xbd_softc* d_drv1; } ;

/* Variables and functions */
 int ENOTTY ; 
 int ENXIO ; 

__attribute__((used)) static int
xbd_ioctl(struct disk *dp, u_long cmd, void *addr, int flag, struct thread *td)
{
	struct xbd_softc *sc = dp->d_drv1;

	if (sc == NULL)
		return (ENXIO);

	return (ENOTTY);
}