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
typedef  int /*<<< orphan*/  uint8_t ;
struct mfi_query_disk {int /*<<< orphan*/  present; int /*<<< orphan*/  array_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  MFIIO_QUERY_DISK ; 
 int /*<<< orphan*/  bzero (struct mfi_query_disk*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct mfi_query_disk*) ; 

__attribute__((used)) static int
mfi_query_disk(int fd, uint8_t target_id, struct mfi_query_disk *info)
{

	bzero(info, sizeof(*info));
	info->array_id = target_id;
	if (ioctl(fd, MFIIO_QUERY_DISK, info) < 0)
		return (-1);
	if (!info->present) {
		errno = ENXIO;
		return (-1);
	}
	return (0);
}