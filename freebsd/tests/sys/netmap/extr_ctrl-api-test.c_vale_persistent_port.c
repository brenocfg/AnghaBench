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
struct nmreq_vale_newif {int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_mem_id; } ;
struct nmreq_header {uintptr_t nr_body; int /*<<< orphan*/  nr_reqtype; } ;
struct TestContext {char* ifname_ext; int /*<<< orphan*/  fd; int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_mem_id; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_REQ_VALE_DELIF ; 
 int /*<<< orphan*/  NETMAP_REQ_VALE_NEWIF ; 
 int /*<<< orphan*/  NIOCCTRL ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nmreq_header*) ; 
 int /*<<< orphan*/  memset (struct nmreq_vale_newif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nmreq_hdr_init (struct nmreq_header*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int vale_attach_detach (struct TestContext*) ; 

__attribute__((used)) static int
vale_persistent_port(struct TestContext *ctx)
{
	struct nmreq_vale_newif req;
	struct nmreq_header hdr;
	int result;
	int ret;

	strncpy(ctx->ifname_ext, "per4", sizeof(ctx->ifname_ext));

	printf("Testing NETMAP_REQ_VALE_NEWIF on '%s'\n", ctx->ifname_ext);

	nmreq_hdr_init(&hdr, ctx->ifname_ext);
	hdr.nr_reqtype = NETMAP_REQ_VALE_NEWIF;
	hdr.nr_body    = (uintptr_t)&req;
	memset(&req, 0, sizeof(req));
	req.nr_mem_id   = ctx->nr_mem_id;
	req.nr_tx_slots = ctx->nr_tx_slots;
	req.nr_rx_slots = ctx->nr_rx_slots;
	req.nr_tx_rings = ctx->nr_tx_rings;
	req.nr_rx_rings = ctx->nr_rx_rings;
	ret             = ioctl(ctx->fd, NIOCCTRL, &hdr);
	if (ret != 0) {
		perror("ioctl(/dev/netmap, NIOCCTRL, VALE_NEWIF)");
		return ret;
	}

	/* Attach the persistent VALE port to a switch and then detach. */
	result = vale_attach_detach(ctx);

	printf("Testing NETMAP_REQ_VALE_DELIF on '%s'\n", ctx->ifname_ext);
	hdr.nr_reqtype = NETMAP_REQ_VALE_DELIF;
	hdr.nr_body    = (uintptr_t)NULL;
	ret            = ioctl(ctx->fd, NIOCCTRL, &hdr);
	if (ret != 0) {
		perror("ioctl(/dev/netmap, NIOCCTRL, VALE_NEWIF)");
		if (result == 0) {
			result = ret;
		}
	}

	return result;
}