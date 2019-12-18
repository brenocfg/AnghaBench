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
struct ctx {int con_net_stat; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  at_cmd_async (int /*<<< orphan*/ ,char*) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  timers ; 
 int /*<<< orphan*/  tmr_add (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct ctx*) ; 
 int /*<<< orphan*/  tmr_creg ; 

__attribute__((used)) static void
at_async_creg(void *arg, const char *resp)
{
	struct ctx *ctx = arg;
	int n, reg;

	n = sscanf(resp, "+CREG: %*d,%d", &reg);
	if (n != 1) {
		n = sscanf(resp, "+CREG: %d", &reg);
		if (n != 1)
			return;
	}

	if (ctx->con_net_stat != 1 && ctx->con_net_stat != 5) {
		tmr_add(&timers, 1, 1, tmr_creg, ctx);
	}
	else {
		tmr_add(&timers, 1, 30, tmr_creg, ctx);
	}

	if (ctx->con_net_stat == reg)
		return;

	ctx->con_net_stat = reg;
	at_cmd_async(ctx->fd, "AT+COPS?\r\n");
}