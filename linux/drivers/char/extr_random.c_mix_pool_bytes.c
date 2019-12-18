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
struct entropy_store {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  _mix_pool_bytes (struct entropy_store*,void const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_mix_pool_bytes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mix_pool_bytes(struct entropy_store *r, const void *in,
			   int nbytes)
{
	unsigned long flags;

	trace_mix_pool_bytes(r->name, nbytes, _RET_IP_);
	spin_lock_irqsave(&r->lock, flags);
	_mix_pool_bytes(r, in, nbytes);
	spin_unlock_irqrestore(&r->lock, flags);
}