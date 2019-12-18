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
struct thread {int dummy; } ;
struct cdev {int /*<<< orphan*/ * si_drv1; } ;
typedef  int /*<<< orphan*/  ips_softc_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ips_ioctl_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ips_ioctl(struct cdev *dev, u_long command, caddr_t addr, int32_t flags, struct thread *td)
{
	ips_softc_t *sc;

	sc = dev->si_drv1;
	return ips_ioctl_request(sc, command, addr, flags);
}