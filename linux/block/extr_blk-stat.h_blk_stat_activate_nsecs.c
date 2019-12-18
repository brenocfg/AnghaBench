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
typedef  int /*<<< orphan*/  u64 ;
struct blk_stat_callback {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ nsecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void blk_stat_activate_nsecs(struct blk_stat_callback *cb,
					   u64 nsecs)
{
	mod_timer(&cb->timer, jiffies + nsecs_to_jiffies(nsecs));
}