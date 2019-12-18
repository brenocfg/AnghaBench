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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_SEM2_UNLOCK ; 
 int qla_flash_protect (int /*<<< orphan*/ *) ; 
 int qla_flash_unprotect (int /*<<< orphan*/ *) ; 
 scalar_t__ qla_flash_write (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int qla_p3p_sem_lock2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_sem_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qla_wait_for_flash_protect (int /*<<< orphan*/ *) ; 
 int qla_wait_for_flash_unprotect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla_flash_write_pattern(qla_host_t *ha, uint32_t off, uint32_t size,
	uint32_t pattern)
{
	int rval = 0;
	uint32_t start;


	if ((rval = qla_p3p_sem_lock2(ha)))
		goto qla_wr_pattern_exit;

	if ((rval = qla_flash_unprotect(ha)))
		goto qla_wr_pattern_unlock_exit;

	if ((rval = qla_wait_for_flash_unprotect(ha)))
		goto qla_wr_pattern_unlock_exit;

	for (start = off; start < (off + size); start = start + 4) {
		if (qla_flash_write(ha, start, pattern)) {
			rval = -1;
			break;
		}
	}

	rval = qla_flash_protect(ha);

	if (rval == 0)
		rval = qla_wait_for_flash_protect(ha);

qla_wr_pattern_unlock_exit:
	qla_sem_unlock(ha, Q8_SEM2_UNLOCK);

qla_wr_pattern_exit:
	return (rval);
}