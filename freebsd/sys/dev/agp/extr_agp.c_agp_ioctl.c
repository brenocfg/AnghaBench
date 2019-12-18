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
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  agp_unbind ;
typedef  int /*<<< orphan*/  agp_setup ;
typedef  int /*<<< orphan*/  agp_info ;
typedef  int /*<<< orphan*/  agp_bind ;
typedef  int /*<<< orphan*/  agp_allocate ;

/* Variables and functions */
#define  AGPIOC_ACQUIRE 136 
#define  AGPIOC_ALLOCATE 135 
#define  AGPIOC_BIND 134 
#define  AGPIOC_CHIPSET_FLUSH 133 
#define  AGPIOC_DEALLOCATE 132 
#define  AGPIOC_INFO 131 
#define  AGPIOC_RELEASE 130 
#define  AGPIOC_SETUP 129 
#define  AGPIOC_UNBIND 128 
 int /*<<< orphan*/  AGP_ACQUIRE_USER ; 
 int EINVAL ; 
 int agp_acquire_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int agp_allocate_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int agp_bind_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int agp_chipset_flush (int /*<<< orphan*/ ) ; 
 int agp_deallocate_user (int /*<<< orphan*/ ,int) ; 
 int agp_info_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int agp_release_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int agp_setup_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int agp_unbind_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
agp_ioctl(struct cdev *kdev, u_long cmd, caddr_t data, int fflag, struct thread *td)
{
	device_t dev = kdev->si_drv1;

	switch (cmd) {
	case AGPIOC_INFO:
		return agp_info_user(dev, (agp_info *) data);

	case AGPIOC_ACQUIRE:
		return agp_acquire_helper(dev, AGP_ACQUIRE_USER);

	case AGPIOC_RELEASE:
		return agp_release_helper(dev, AGP_ACQUIRE_USER);

	case AGPIOC_SETUP:
		return agp_setup_user(dev, (agp_setup *)data);

	case AGPIOC_ALLOCATE:
		return agp_allocate_user(dev, (agp_allocate *)data);

	case AGPIOC_DEALLOCATE:
		return agp_deallocate_user(dev, *(int *) data);

	case AGPIOC_BIND:
		return agp_bind_user(dev, (agp_bind *)data);

	case AGPIOC_UNBIND:
		return agp_unbind_user(dev, (agp_unbind *)data);

	case AGPIOC_CHIPSET_FLUSH:
		return agp_chipset_flush(dev);
	}

	return EINVAL;
}