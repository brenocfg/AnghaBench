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
struct twe_softc {int dummy; } ;
struct thread {int dummy; } ;
struct cdev {scalar_t__ si_drv1; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int twe_ioctl (struct twe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twe_ioctl_wrapper(struct cdev *dev, u_long cmd, caddr_t addr, int32_t flag, struct thread *td)
{
    struct twe_softc		*sc = (struct twe_softc *)dev->si_drv1;
    
    return(twe_ioctl(sc, cmd, addr));
}