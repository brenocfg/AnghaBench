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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 scalar_t__ qla_flash_wait_for_write_complete (int /*<<< orphan*/ *) ; 
 scalar_t__ qla_flash_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qla_flash_write_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla_flash_write(qla_host_t *ha, uint32_t off, uint32_t data)
{
	if (qla_flash_write_enable(ha) != 0) 
		return(-1);

	if (qla_flash_write32(ha, off, data) != 0)
		return -1;

	if (qla_flash_wait_for_write_complete(ha))
		return -1;

	return 0;
}