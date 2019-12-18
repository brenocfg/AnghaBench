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
struct ctx {int con_status; size_t con_net_type; int /*<<< orphan*/  con_apn; int /*<<< orphan*/  con_oper; int /*<<< orphan*/  pdp_ctx; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  at_cmd_async (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * network_access_type ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static void
at_async_owancall(void *arg, const char *resp)
{
	struct ctx *ctx = arg;
	int n, i;

	n = sscanf(resp, "_OWANCALL: %*d,%d", &i);
	if (n != 1)
		return;

	if (i == ctx->con_status)
		return;

	at_cmd_async(ctx->fd, "AT_OWANDATA=%d\r\n", ctx->pdp_ctx);

	ctx->con_status = i;
	if (ctx->con_status == 1) {
		logger(LOG_NOTICE, "Connected to \"%s\" (%s), %s",
		    ctx->con_oper, ctx->con_apn,
		    network_access_type[ctx->con_net_type]);
	}
	else {
		logger(LOG_NOTICE, "Disconnected from \"%s\" (%s)",
		    ctx->con_oper, ctx->con_apn);
	}
}