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
struct fw_transaction {int /*<<< orphan*/  split_timeout_timer; scalar_t__ is_split_transaction; } ;

/* Variables and functions */
 int del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_cancel_split_timeout(struct fw_transaction *t)
{
	if (t->is_split_transaction)
		return del_timer(&t->split_timeout_timer);
	else
		return 1;
}