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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct spigen_transfer_mmapped {int dummy; } ;
struct spigen_transfer {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTTY ; 
#define  SPIGENIOC_GET_CLOCK_SPEED 133 
#define  SPIGENIOC_GET_SPI_MODE 132 
#define  SPIGENIOC_SET_CLOCK_SPEED 131 
#define  SPIGENIOC_SET_SPI_MODE 130 
#define  SPIGENIOC_TRANSFER 129 
#define  SPIGENIOC_TRANSFER_MMAPPED 128 
 int spibus_get_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spibus_get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int spibus_set_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spibus_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spigen_transfer (struct cdev*,struct spigen_transfer*) ; 
 int spigen_transfer_mmapped (struct cdev*,struct spigen_transfer_mmapped*) ; 

__attribute__((used)) static int
spigen_ioctl(struct cdev *cdev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	device_t dev = cdev->si_drv1;
	int error;

	switch (cmd) {
	case SPIGENIOC_TRANSFER:
		error = spigen_transfer(cdev, (struct spigen_transfer *)data);
		break;
	case SPIGENIOC_TRANSFER_MMAPPED:
		error = spigen_transfer_mmapped(cdev, (struct spigen_transfer_mmapped *)data);
		break;
	case SPIGENIOC_GET_CLOCK_SPEED:
		error = spibus_get_clock(dev, (uint32_t *)data);
		break;
	case SPIGENIOC_SET_CLOCK_SPEED:
		error = spibus_set_clock(dev, *(uint32_t *)data);
		break;
	case SPIGENIOC_GET_SPI_MODE:
		error = spibus_get_mode(dev, (uint32_t *)data);
		break;
	case SPIGENIOC_SET_SPI_MODE:
		error = spibus_set_mode(dev, *(uint32_t *)data);
		break;
	default:
		error = ENOTTY;
		break;
	}
	return (error);
}