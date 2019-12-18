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
typedef  int /*<<< orphan*/  ulong ;

/* Variables and functions */
 int /*<<< orphan*/  AOE_PARTITIONS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  N_DEVS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  used_minors ; 
 int /*<<< orphan*/  used_minors_lock ; 

__attribute__((used)) static void
minor_free(ulong minor)
{
	ulong flags;

	minor /= AOE_PARTITIONS;
	BUG_ON(minor >= N_DEVS);

	spin_lock_irqsave(&used_minors_lock, flags);
	BUG_ON(!test_bit(minor, used_minors));
	clear_bit(minor, used_minors);
	spin_unlock_irqrestore(&used_minors_lock, flags);
}