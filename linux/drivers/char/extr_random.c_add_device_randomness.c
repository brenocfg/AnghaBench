#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  _mix_pool_bytes (TYPE_1__*,unsigned long*,int) ; 
 int /*<<< orphan*/  crng_ready () ; 
 int /*<<< orphan*/  crng_slow_load (void const*,unsigned int) ; 
 TYPE_1__ input_pool ; 
 unsigned long jiffies ; 
 unsigned long random_get_entropy () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_add_device_randomness (unsigned int,int /*<<< orphan*/ ) ; 

void add_device_randomness(const void *buf, unsigned int size)
{
	unsigned long time = random_get_entropy() ^ jiffies;
	unsigned long flags;

	if (!crng_ready() && size)
		crng_slow_load(buf, size);

	trace_add_device_randomness(size, _RET_IP_);
	spin_lock_irqsave(&input_pool.lock, flags);
	_mix_pool_bytes(&input_pool, buf, size);
	_mix_pool_bytes(&input_pool, &time, sizeof(time));
	spin_unlock_irqrestore(&input_pool.lock, flags);
}