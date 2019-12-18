#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comm_base {TYPE_1__* eb; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ub_event_base_loopexit (int /*<<< orphan*/ ) ; 

void comm_base_exit(struct comm_base* b)
{
	if(ub_event_base_loopexit(b->eb->base) != 0) {
		log_err("Could not loopexit");
	}
}