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
struct tableop_state {void* tc; int modified; } ;
struct op_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
restart_flush(void *object, struct op_state *_state)
{
	struct tableop_state *ts;

	ts = (struct tableop_state *)_state;

	if (ts->tc != object)
		return;

	/* Indicate we've called */
	ts->modified = 1;
}