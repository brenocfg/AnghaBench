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
struct thread {int dummy; } ;
struct hpet_softc {int /*<<< orphan*/  mmap_allow; } ;
struct cdev {struct hpet_softc* si_drv1; } ;

/* Variables and functions */
 int EPERM ; 

__attribute__((used)) static int
hpet_open(struct cdev *cdev, int oflags, int devtype, struct thread *td)
{
	struct hpet_softc *sc;

	sc = cdev->si_drv1;
	if (!sc->mmap_allow)
		return (EPERM);
	else
		return (0);
}