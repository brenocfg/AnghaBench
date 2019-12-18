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
struct blk_stat_callback {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_stat_free_callback_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blk_stat_free_callback(struct blk_stat_callback *cb)
{
	if (cb)
		call_rcu(&cb->rcu, blk_stat_free_callback_rcu);
}