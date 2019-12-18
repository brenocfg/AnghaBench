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
typedef  int time_t ;
struct renew_ctx {int /*<<< orphan*/  principal; int /*<<< orphan*/  ccache; int /*<<< orphan*/  context; int /*<<< orphan*/  ticket_life; } ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 scalar_t__ do_afslog ; 
 int /*<<< orphan*/  get_new_tickets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ k_hasafs () ; 
 int /*<<< orphan*/  krb5_afslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ renew_validate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ renewable_flag ; 
 int /*<<< orphan*/  server_str ; 
 int ticket_lifetime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_flag ; 

__attribute__((used)) static time_t
renew_func(void *ptr)
{
    struct renew_ctx *ctx = ptr;
    krb5_error_code ret;
    time_t expire;
    int new_tickets = 0;

    if (renewable_flag) {
	ret = renew_validate(ctx->context, renewable_flag, validate_flag,
			     ctx->ccache, server_str, ctx->ticket_life);
	if (ret)
	    new_tickets = 1;
    } else
	new_tickets = 1;

    if (new_tickets)
	get_new_tickets(ctx->context, ctx->principal,
			ctx->ccache, ctx->ticket_life, 0);

#ifndef NO_AFS
    if(do_afslog && k_hasafs())
	krb5_afslog(ctx->context, ctx->ccache, NULL, NULL);
#endif

    expire = ticket_lifetime(ctx->context, ctx->ccache, ctx->principal,
			     server_str) / 2;
    return expire + 1;
}