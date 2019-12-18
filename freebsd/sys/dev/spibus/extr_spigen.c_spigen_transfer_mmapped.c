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
struct spigen_transfer_mmapped {scalar_t__ stm_command_length; scalar_t__ stm_data_length; } ;
struct spigen_mmap {scalar_t__ bufsize; scalar_t__ kvaddr; } ;
struct spi_command {scalar_t__ tx_cmd_sz; scalar_t__ rx_cmd_sz; scalar_t__ tx_data_sz; scalar_t__ rx_data_sz; void* rx_data; void* tx_data; void* rx_cmd; void* tx_cmd; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int E2BIG ; 
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 
 struct spi_command SPI_COMMAND_INITIALIZER ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spigen_transfer_mmapped(struct cdev *cdev, struct spigen_transfer_mmapped *stm)
{
	struct spi_command transfer = SPI_COMMAND_INITIALIZER;
	device_t dev = cdev->si_drv1;
	struct spigen_mmap *mmap;
	int error;

	if ((error = devfs_get_cdevpriv((void **)&mmap)) != 0)
		return (error);

	if (mmap->bufsize < stm->stm_command_length + stm->stm_data_length)
		return (E2BIG);

	transfer.tx_cmd = transfer.rx_cmd = (void *)((uintptr_t)mmap->kvaddr);
	transfer.tx_cmd_sz = transfer.rx_cmd_sz = stm->stm_command_length;
	transfer.tx_data = transfer.rx_data =
	    (void *)((uintptr_t)mmap->kvaddr + stm->stm_command_length);
	transfer.tx_data_sz = transfer.rx_data_sz = stm->stm_data_length;
	error = SPIBUS_TRANSFER(device_get_parent(dev), dev, &transfer);

	return (error);
}