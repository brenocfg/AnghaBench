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
struct spi_command {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spibus_transfer_impl(device_t dev, device_t child, struct spi_command *cmd)
{
	return (SPIBUS_TRANSFER(device_get_parent(dev), child, cmd));
}