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
typedef  int /*<<< orphan*/  uint16_t ;
struct mfi_pd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_PD_GET_INFO ; 
 int /*<<< orphan*/  mbox_store_device_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_pd_info*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
mfi_pd_get_info(int fd, uint16_t device_id, struct mfi_pd_info *info,
    uint8_t *statusp)
{
	uint8_t mbox[2];

	mbox_store_device_id(&mbox[0], device_id);
	return (mfi_dcmd_command(fd, MFI_DCMD_PD_GET_INFO, info,
	    sizeof(struct mfi_pd_info), mbox, 2, statusp));
}