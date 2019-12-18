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
struct mfi_evt_ld {int /*<<< orphan*/  target_id; } ;

/* Variables and functions */
 char const* mfi_volume_name (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
volume_name(int fd, struct mfi_evt_ld *ld)
{

	return (mfi_volume_name(fd, ld->target_id));
}