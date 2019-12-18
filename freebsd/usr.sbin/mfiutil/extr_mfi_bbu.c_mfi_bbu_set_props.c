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
struct mfi_bbu_properties {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_DCMD_BBU_SET_PROP ; 
 int mfi_dcmd_command (int,int /*<<< orphan*/ ,struct mfi_bbu_properties*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
mfi_bbu_set_props(int fd, struct mfi_bbu_properties *props, uint8_t *statusp)
{

	return (mfi_dcmd_command(fd, MFI_DCMD_BBU_SET_PROP, props,
	    sizeof(*props), NULL, 0, statusp));
}