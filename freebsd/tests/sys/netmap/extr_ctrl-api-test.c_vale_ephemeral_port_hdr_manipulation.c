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
struct TestContext {scalar_t__ nr_hdr_len; int /*<<< orphan*/  nr_mode; int /*<<< orphan*/  ifname_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_REG_ALL_NIC ; 
 scalar_t__ VIRTIO_NET_HDR_LEN ; 
 scalar_t__ VIRTIO_NET_HDR_LEN_WITH_MERGEABLE_RXBUFS ; 
 int port_hdr_set_and_get (struct TestContext*) ; 
 int port_register (struct TestContext*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
vale_ephemeral_port_hdr_manipulation(struct TestContext *ctx)
{
	int ret;

	strncpy(ctx->ifname_ext, "vale:eph0", sizeof(ctx->ifname_ext));
	ctx->nr_mode = NR_REG_ALL_NIC;
	if ((ret = port_register(ctx))) {
		return ret;
	}
	/* Try to set and get all the acceptable values. */
	ctx->nr_hdr_len = VIRTIO_NET_HDR_LEN_WITH_MERGEABLE_RXBUFS;
	if ((ret = port_hdr_set_and_get(ctx))) {
		return ret;
	}
	ctx->nr_hdr_len = 0;
	if ((ret = port_hdr_set_and_get(ctx))) {
		return ret;
	}
	ctx->nr_hdr_len = VIRTIO_NET_HDR_LEN;
	if ((ret = port_hdr_set_and_get(ctx))) {
		return ret;
	}
	return 0;
}