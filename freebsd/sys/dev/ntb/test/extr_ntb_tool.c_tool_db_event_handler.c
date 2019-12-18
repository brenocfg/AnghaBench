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
typedef  int uint64_t ;
struct tool_ctx {int db_event_val; int /*<<< orphan*/  db_event_timer; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct tool_ctx*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ntb_db_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tool_db_event_handler(void *arg)
{
	struct tool_ctx *tc = (struct tool_ctx *)arg;
	uint64_t db_bits;

	db_bits = ntb_db_read(tc->dev);

	if (db_bits == tc->db_event_val) {
		device_printf(tc->dev, "db_event successful for db val=0x%jx\n",
		    tc->db_event_val);
		tc->db_event_val = 0x0;
	} else
		callout_reset(&tc->db_event_timer, 1, tool_db_event_handler, tc);
}