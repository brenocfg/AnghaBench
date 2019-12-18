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
struct ctx {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  at_cmd_async (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  watchdog_reset (struct ctx*,int) ; 

__attribute__((used)) static void
tmr_cgreg(int id, void *arg)
{
	struct ctx *ctx = arg;

	at_cmd_async(ctx->fd, "AT+CGREG?\r\n");
	watchdog_reset(ctx, 10);
}