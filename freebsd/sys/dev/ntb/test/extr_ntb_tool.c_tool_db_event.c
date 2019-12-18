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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tool_ctx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 scalar_t__ ntb_db_read (int /*<<< orphan*/ ) ; 
 scalar_t__ ntb_db_vector_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tool_db_event(void *ctx, uint32_t vec)
{
	struct tool_ctx *tc = ctx;
	uint64_t db_bits, db_mask;

	db_mask = ntb_db_vector_mask(tc->dev, vec);
	db_bits = ntb_db_read(tc->dev);

	device_printf(tc->dev, "doorbell vec %d mask %#llx bits %#llx\n",
	    vec, (unsigned long long)db_mask, (unsigned long long)db_bits);
}