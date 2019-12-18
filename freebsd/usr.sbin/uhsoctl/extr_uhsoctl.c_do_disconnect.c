#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct ctx {int flags; int /*<<< orphan*/  resolv_path; int /*<<< orphan*/  ifnam; TYPE_2__ ip; int /*<<< orphan*/  fd; int /*<<< orphan*/  pdp_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int IPASSIGNED ; 
 int /*<<< orphan*/  at_cmd (struct ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_ifdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifaddr_del (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set_nameservers (struct ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_disconnect(struct ctx *ctx)
{
	struct sockaddr_in sin, mask;

	/* Disconnect */
	at_cmd(ctx, NULL, NULL, NULL, "AT_OWANCALL=%d,0,0\r\n",
	    ctx->pdp_ctx);
	close(ctx->fd);

	/* Remove ip-address from interface */
	if (ctx->flags & IPASSIGNED) {
		sin.sin_len = mask.sin_len = sizeof(struct sockaddr_in);
		memset(&mask.sin_addr.s_addr, 0xff,
		    sizeof(mask.sin_addr.s_addr));
		sin.sin_family = mask.sin_family = AF_INET;
		memcpy(&sin.sin_addr.s_addr, &ctx->ip.s_addr,
		    sizeof(sin.sin_addr.s_addr));
		ifaddr_del(ctx->ifnam, (struct sockaddr *)&sin,
		    (struct sockaddr *)&mask);

		if_ifdown(ctx->ifnam);
		ctx->flags &= ~IPASSIGNED;
	}

	/* Attempt to reset resolv.conf */
	set_nameservers(ctx, ctx->resolv_path, 0);
}