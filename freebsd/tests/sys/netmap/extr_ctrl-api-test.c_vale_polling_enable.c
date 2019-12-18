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
typedef  int /*<<< orphan*/  vpname ;
struct nmreq_vale_polling {scalar_t__ nr_mode; scalar_t__ nr_first_cpu_id; scalar_t__ nr_num_polling_cpus; } ;
struct nmreq_header {uintptr_t nr_body; int /*<<< orphan*/  nr_reqtype; } ;
struct TestContext {char* bdgname; char* ifname_ext; scalar_t__ nr_mode; scalar_t__ nr_first_cpu_id; scalar_t__ nr_num_polling_cpus; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_REQ_VALE_POLLING_ENABLE ; 
 int /*<<< orphan*/  NIOCCTRL ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nmreq_header*) ; 
 int /*<<< orphan*/  memset (struct nmreq_vale_polling*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nmreq_hdr_init (struct nmreq_header*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int
vale_polling_enable(struct TestContext *ctx)
{
	struct nmreq_vale_polling req;
	struct nmreq_header hdr;
	char vpname[256];
	int ret;

	snprintf(vpname, sizeof(vpname), "%s:%s", ctx->bdgname, ctx->ifname_ext);
	printf("Testing NETMAP_REQ_VALE_POLLING_ENABLE on '%s'\n", vpname);

	nmreq_hdr_init(&hdr, vpname);
	hdr.nr_reqtype = NETMAP_REQ_VALE_POLLING_ENABLE;
	hdr.nr_body    = (uintptr_t)&req;
	memset(&req, 0, sizeof(req));
	req.nr_mode             = ctx->nr_mode;
	req.nr_first_cpu_id     = ctx->nr_first_cpu_id;
	req.nr_num_polling_cpus = ctx->nr_num_polling_cpus;
	ret                     = ioctl(ctx->fd, NIOCCTRL, &hdr);
	if (ret != 0) {
		perror("ioctl(/dev/netmap, NIOCCTRL, VALE_POLLING_ENABLE)");
		return ret;
	}

	return (req.nr_mode == ctx->nr_mode &&
	        req.nr_first_cpu_id == ctx->nr_first_cpu_id &&
	        req.nr_num_polling_cpus == ctx->nr_num_polling_cpus)
	               ? 0
	               : -1;
}