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
struct ctx {int con_net_type; int con_net_stat; int con_status; int /*<<< orphan*/  pdp_ctx; int /*<<< orphan*/  fd; int /*<<< orphan*/ * con_oper; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  at_cmd_async (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * network_access_type ; 
 int /*<<< orphan*/ * network_reg_status ; 
 int sscanf (char const*,char*,char*,int*) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static void
at_async_cops(void *arg, const char *resp)
{
	struct ctx *ctx = arg;
	int n, at;
	char opr[64];

	n = sscanf(resp, "+COPS: %*d,%*d,\"%[^\"]\",%d",
	    opr, &at);
	if (n != 2)
		return;

	if (ctx->con_oper != NULL) {
		if (ctx->con_net_type == at &&
		    strcasecmp(opr, ctx->con_oper) == 0)
			return;
		free(ctx->con_oper);
	}

	ctx->con_oper = strdup(opr);
	ctx->con_net_type = at;

	if (ctx->con_net_stat == 1 || ctx->con_net_stat == 5) {
		logger(LOG_NOTICE, "%s to \"%s\" (%s)",
		    network_reg_status[ctx->con_net_stat],
		    ctx->con_oper, network_access_type[ctx->con_net_type]);
		if (ctx->con_status != 1) {
			at_cmd_async(ctx->fd, "AT_OWANCALL=%d,1,1\r\n",
			    ctx->pdp_ctx);
		}
	}
	else {
		logger(LOG_NOTICE, "%s (%s)",
		    network_reg_status[ctx->con_net_stat],
		    network_access_type[ctx->con_net_type]);
	}
}