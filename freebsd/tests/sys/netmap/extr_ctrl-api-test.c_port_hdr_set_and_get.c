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
struct nmreq_port_hdr {scalar_t__ nr_hdr_len; } ;
struct nmreq_header {uintptr_t nr_body; int /*<<< orphan*/  nr_reqtype; } ;
struct TestContext {scalar_t__ ifname_ext; scalar_t__ nr_hdr_len; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_REQ_PORT_HDR_GET ; 
 int /*<<< orphan*/  NETMAP_REQ_PORT_HDR_SET ; 
 int /*<<< orphan*/  NIOCCTRL ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nmreq_header*) ; 
 int /*<<< orphan*/  memset (struct nmreq_port_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nmreq_hdr_init (struct nmreq_header*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static int
port_hdr_set_and_get(struct TestContext *ctx)
{
	struct nmreq_port_hdr req;
	struct nmreq_header hdr;
	int ret;

	printf("Testing NETMAP_REQ_PORT_HDR_SET on '%s'\n", ctx->ifname_ext);

	nmreq_hdr_init(&hdr, ctx->ifname_ext);
	hdr.nr_reqtype = NETMAP_REQ_PORT_HDR_SET;
	hdr.nr_body    = (uintptr_t)&req;
	memset(&req, 0, sizeof(req));
	req.nr_hdr_len = ctx->nr_hdr_len;
	ret            = ioctl(ctx->fd, NIOCCTRL, &hdr);
	if (ret != 0) {
		perror("ioctl(/dev/netmap, NIOCCTRL, PORT_HDR_SET)");
		return ret;
	}

	if (req.nr_hdr_len != ctx->nr_hdr_len) {
		return -1;
	}

	printf("Testing NETMAP_REQ_PORT_HDR_GET on '%s'\n", ctx->ifname_ext);
	hdr.nr_reqtype = NETMAP_REQ_PORT_HDR_GET;
	req.nr_hdr_len = 0;
	ret            = ioctl(ctx->fd, NIOCCTRL, &hdr);
	if (ret != 0) {
		perror("ioctl(/dev/netmap, NIOCCTRL, PORT_HDR_SET)");
		return ret;
	}
	printf("nr_hdr_len %u\n", req.nr_hdr_len);

	return (req.nr_hdr_len == ctx->nr_hdr_len) ? 0 : -1;
}