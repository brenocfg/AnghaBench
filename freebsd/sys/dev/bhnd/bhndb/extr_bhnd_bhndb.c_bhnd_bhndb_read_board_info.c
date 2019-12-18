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
struct bhnd_board_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHNDB_POPULATE_BOARD_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_board_info*) ; 
 int bhnd_bus_generic_read_board_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_board_info*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_bhndb_read_board_info(device_t dev, device_t child,
    struct bhnd_board_info *info)
{
	int	error;

	/* Initialize with NVRAM-derived values */
	if ((error = bhnd_bus_generic_read_board_info(dev, child, info)))
		return (error);

	/* Let the bridge fill in any additional data */
	return (BHNDB_POPULATE_BOARD_INFO(device_get_parent(dev), dev, info));
}