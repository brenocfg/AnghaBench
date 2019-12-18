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
struct mfi_ld_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_LD_GET_LIST ; 
 int mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_ld_list*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mfi_ld_get_list(int fd, struct mfi_ld_list *list, uint8_t *statusp)
{

	return (mfi_dcmd_command(fd, MFI_DCMD_LD_GET_LIST, list,
		sizeof(struct mfi_ld_list), NULL, 0, statusp));
}