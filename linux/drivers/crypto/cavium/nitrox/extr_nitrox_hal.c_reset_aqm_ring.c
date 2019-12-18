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
union aqmq_en {void* value; scalar_t__ queue_enable; } ;
union aqmq_cmp_cnt {void* value; } ;
union aqmq_activity_stat {int /*<<< orphan*/  queue_active; void* value; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQMQ_ACTIVITY_STATX (int) ; 
 int /*<<< orphan*/  AQMQ_CMP_CNTX (int) ; 
 int /*<<< orphan*/  AQMQ_ENX (int) ; 
 int MAX_CSR_RETRIES ; 
 void* nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void reset_aqm_ring(struct nitrox_device *ndev, int ring)
{
	union aqmq_en aqmq_en_reg;
	union aqmq_activity_stat activity_stat;
	union aqmq_cmp_cnt cmp_cnt;
	int max_retries = MAX_CSR_RETRIES;
	u64 offset;

	/* step 1: disable the queue */
	offset = AQMQ_ENX(ring);
	aqmq_en_reg.value = 0;
	aqmq_en_reg.queue_enable = 0;
	nitrox_write_csr(ndev, offset, aqmq_en_reg.value);

	/* step 2: wait for AQMQ_ACTIVITY_STATX[QUEUE_ACTIVE] to clear */
	usleep_range(100, 150);
	offset = AQMQ_ACTIVITY_STATX(ring);
	do {
		activity_stat.value = nitrox_read_csr(ndev, offset);
		if (!activity_stat.queue_active)
			break;
		udelay(50);
	} while (max_retries--);

	/* step 3: clear commands completed count */
	offset = AQMQ_CMP_CNTX(ring);
	cmp_cnt.value = nitrox_read_csr(ndev, offset);
	nitrox_write_csr(ndev, offset, cmp_cnt.value);
	usleep_range(50, 100);
}