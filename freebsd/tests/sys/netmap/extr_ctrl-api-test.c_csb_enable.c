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
struct nmreq_option {scalar_t__ nro_status; } ;
struct nmreq_opt_csb {struct nmreq_option nro_opt; } ;
struct nmreq_header {uintptr_t nr_options; uintptr_t nr_body; int /*<<< orphan*/  nr_reqtype; } ;
struct TestContext {char* ifname_ext; int /*<<< orphan*/  fd; scalar_t__ nr_opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_REQ_CSB_ENABLE ; 
 int /*<<< orphan*/  NIOCCTRL ; 
 int checkoption (struct nmreq_option*,struct nmreq_option*) ; 
 int /*<<< orphan*/  clear_options (struct TestContext*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nmreq_header*) ; 
 int /*<<< orphan*/  nmreq_hdr_init (struct nmreq_header*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int push_csb_option (struct TestContext*,struct nmreq_opt_csb*) ; 

__attribute__((used)) static int
csb_enable(struct TestContext *ctx)
{
	struct nmreq_option saveopt;
	struct nmreq_opt_csb opt;
	struct nmreq_header hdr;
	int ret;

	ret = push_csb_option(ctx, &opt);
	if (ret != 0) {
		return ret;
	}
	saveopt = opt.nro_opt;
	saveopt.nro_status = 0;

	nmreq_hdr_init(&hdr, ctx->ifname_ext);
	hdr.nr_reqtype = NETMAP_REQ_CSB_ENABLE;
	hdr.nr_options = (uintptr_t)ctx->nr_opt;
	hdr.nr_body = (uintptr_t)NULL;

	printf("Testing NETMAP_REQ_CSB_ENABLE on '%s'\n", ctx->ifname_ext);

	ret           = ioctl(ctx->fd, NIOCCTRL, &hdr);
	if (ret != 0) {
		perror("ioctl(/dev/netmap, NIOCCTRL, CSB_ENABLE)");
		return ret;
	}

	ret = checkoption(&opt.nro_opt, &saveopt);
	clear_options(ctx);

	return ret;
}