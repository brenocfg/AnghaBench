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

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_TIME_SECS_GET ; 
 scalar_t__ mfi_dcmd_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
mfi_get_time(int fd, uint32_t *at)
{

	if (mfi_dcmd_command(fd, MFI_DCMD_TIME_SECS_GET, at, sizeof(*at), NULL,
	    0, NULL) < 0) {
		warn("Couldn't fetch adapter time");
		at = 0;
	}
}