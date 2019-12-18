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
typedef  int u8 ;
typedef  int /*<<< orphan*/  dvfs_idx ;
typedef  int /*<<< orphan*/  domain ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_DVFS ; 
 int scpi_send_message (int /*<<< orphan*/ ,int*,int,int*,int) ; 

__attribute__((used)) static int scpi_dvfs_get_idx(u8 domain)
{
	int ret;
	u8 dvfs_idx;

	ret = scpi_send_message(CMD_GET_DVFS, &domain, sizeof(domain),
				&dvfs_idx, sizeof(dvfs_idx));

	return ret ? ret : dvfs_idx;
}