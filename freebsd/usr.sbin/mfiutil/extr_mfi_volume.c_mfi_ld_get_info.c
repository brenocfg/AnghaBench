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
struct mfi_ld_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_LD_GET_INFO ; 
 int mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_ld_info*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
mfi_ld_get_info(int fd, uint8_t target_id, struct mfi_ld_info *info,
    uint8_t *statusp)
{
	uint8_t mbox[1];

	mbox[0] = target_id;
	return (mfi_dcmd_command(fd, MFI_DCMD_LD_GET_INFO, info,
	    sizeof(struct mfi_ld_info), mbox, 1, statusp));
}