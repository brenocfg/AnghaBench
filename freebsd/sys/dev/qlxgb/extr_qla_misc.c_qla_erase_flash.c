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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int Q8_FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  Q8_SEM2_UNLOCK ; 
 scalar_t__ qla_erase_flash_sector (int /*<<< orphan*/ *,int) ; 
 int qla_flash_protect (int /*<<< orphan*/ *) ; 
 int qla_flash_unprotect (int /*<<< orphan*/ *) ; 
 int qla_p3p_sem_lock2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_sem_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qla_wait_for_flash_unprotect (int /*<<< orphan*/ *) ; 

int
qla_erase_flash(qla_host_t *ha, uint32_t off, uint32_t size)
{
	int rval = 0;
	uint32_t start;

	if (off & (Q8_FLASH_SECTOR_SIZE -1))
		return -1;

	if ((rval = qla_p3p_sem_lock2(ha)))
		goto qla_erase_flash_exit;

	if ((rval = qla_flash_unprotect(ha)))
		goto qla_erase_flash_unlock_exit;

	if ((rval = qla_wait_for_flash_unprotect(ha)))
		goto qla_erase_flash_unlock_exit;

	for (start = off; start < (off + size); start = start + 0x10000) {
		if (qla_erase_flash_sector(ha, start)) {
			rval = -1;
			break;
		}
	}

	rval = qla_flash_protect(ha);

qla_erase_flash_unlock_exit:
	qla_sem_unlock(ha, Q8_SEM2_UNLOCK);

qla_erase_flash_exit:
	return (rval);
}