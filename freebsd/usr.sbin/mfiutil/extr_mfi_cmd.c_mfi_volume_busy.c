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
struct mfi_query_disk {scalar_t__ open; } ;

/* Variables and functions */
 scalar_t__ mfi_query_disk (int,int /*<<< orphan*/ ,struct mfi_query_disk*) ; 

int
mfi_volume_busy(int fd, uint8_t target_id)
{
	struct mfi_query_disk info;

	/* Assume it isn't mounted if we can't get information. */
	if (mfi_query_disk(fd, target_id, &info) < 0)
		return (0);
	return (info.open != 0);
}