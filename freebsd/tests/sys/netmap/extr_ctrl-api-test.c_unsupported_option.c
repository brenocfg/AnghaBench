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
struct nmreq_option {int nro_reqtype; int /*<<< orphan*/  nro_status; } ;
struct TestContext {char* ifname_ext; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int checkoption (struct nmreq_option*,struct nmreq_option*) ; 
 int /*<<< orphan*/  clear_options (struct TestContext*) ; 
 int /*<<< orphan*/  memset (struct nmreq_option*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ port_register_hwall (struct TestContext*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  push_option (struct nmreq_option*,struct TestContext*) ; 

__attribute__((used)) static int
unsupported_option(struct TestContext *ctx)
{
	struct nmreq_option opt, save;

	printf("Testing unsupported option on %s\n", ctx->ifname_ext);

	memset(&opt, 0, sizeof(opt));
	opt.nro_reqtype = 1234;
	push_option(&opt, ctx);
	save = opt;

	if (port_register_hwall(ctx) >= 0)
		return -1;

	clear_options(ctx);
	save.nro_status = EOPNOTSUPP;
	return checkoption(&opt, &save);
}