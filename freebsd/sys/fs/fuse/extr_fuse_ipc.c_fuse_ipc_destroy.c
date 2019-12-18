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

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_ticket_count ; 
 int /*<<< orphan*/  ticket_zone ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void
fuse_ipc_destroy(void)
{
	counter_u64_free(fuse_ticket_count);
	uma_zdestroy(ticket_zone);
}