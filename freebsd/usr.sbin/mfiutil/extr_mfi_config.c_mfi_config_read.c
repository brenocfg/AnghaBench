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
struct mfi_config_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_CFG_READ ; 
 int mfi_config_read_opcode (int,int /*<<< orphan*/ ,struct mfi_config_data**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
mfi_config_read(int fd, struct mfi_config_data **configp)
{
	return mfi_config_read_opcode(fd, MFI_DCMD_CFG_READ, configp, NULL, 0);
}