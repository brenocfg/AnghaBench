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
struct tool_ctx {unsigned char link_status; scalar_t__ link_bits; scalar_t__ db_event_val; scalar_t__ peer_db_mask_val; scalar_t__ peer_db_val; scalar_t__ db_mask_val; int /*<<< orphan*/  db_event_timer; int /*<<< orphan*/  link_event_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
tool_check_ntb(struct tool_ctx *tc)
{

	/* create and initialize link callout handler */
	callout_init(&tc->link_event_timer, 1);

	/* create and initialize db callout handler */
	callout_init(&tc->db_event_timer, 1);

	/* Initialize sysctl read out values to default */
	tc->link_status = 'U';
	tc->db_mask_val = 0;
	tc->peer_db_val = 0;
	tc->peer_db_mask_val = 0;
	tc->db_event_val = 0;
	tc->link_bits = 0;

	return (0);
}