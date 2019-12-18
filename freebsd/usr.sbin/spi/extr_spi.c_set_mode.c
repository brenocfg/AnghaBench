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
typedef  scalar_t__ uint32_t ;
struct spi_options {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIGENIOC_SET_SPI_MODE ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
set_mode(int hdev, struct spi_options *popt)
{
	uint32_t fmode = popt->mode;

	if (popt->mode < 0)	/* use default? */
		return 0;

	return ioctl(hdev, SPIGENIOC_SET_SPI_MODE, &fmode);
}