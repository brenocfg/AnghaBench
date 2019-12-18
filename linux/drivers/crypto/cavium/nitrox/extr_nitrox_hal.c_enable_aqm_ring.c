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
union aqmq_en {int queue_enable; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQMQ_ENX (int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void enable_aqm_ring(struct nitrox_device *ndev, int ring)
{
	union aqmq_en aqmq_en_reg;
	u64 offset;

	offset = AQMQ_ENX(ring);
	aqmq_en_reg.value = 0;
	aqmq_en_reg.queue_enable = 1;
	nitrox_write_csr(ndev, offset, aqmq_en_reg.value);
	usleep_range(50, 100);
}