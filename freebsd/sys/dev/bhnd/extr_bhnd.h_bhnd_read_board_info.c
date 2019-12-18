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
 int BHND_BUS_READ_BOARD_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_board_info*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bhnd_read_board_info(device_t dev, struct bhnd_board_info *info)
{
	return (BHND_BUS_READ_BOARD_INFO(device_get_parent(dev), dev, info));
}