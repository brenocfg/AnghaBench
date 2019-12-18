#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_4__ sin_addr; } ;
struct TYPE_7__ {scalar_t__ ps; } ;
struct rdma_id_private {TYPE_1__ id; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  ip6; TYPE_3__ ip4; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  ip6; TYPE_2__ ip4; } ;
struct cma_hdr {TYPE_6__ dst_addr; TYPE_5__ src_addr; int /*<<< orphan*/  port; int /*<<< orphan*/  cma_version; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CMA_VERSION ; 
 scalar_t__ RDMA_PS_SDP ; 
 scalar_t__ cma_dst_addr (struct rdma_id_private*) ; 
 scalar_t__ cma_family (struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_ip6_clear_scope_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cma_set_ip_ver (struct cma_hdr*,int) ; 
 scalar_t__ cma_src_addr (struct rdma_id_private*) ; 
 int sdp_format_hdr (void*,struct rdma_id_private*) ; 

__attribute__((used)) static int cma_format_hdr(void *hdr, struct rdma_id_private *id_priv)
{
	struct cma_hdr *cma_hdr;

	if (id_priv->id.ps == RDMA_PS_SDP)
		return sdp_format_hdr(hdr, id_priv);

	cma_hdr = hdr;
	cma_hdr->cma_version = CMA_VERSION;
	if (cma_family(id_priv) == AF_INET) {
		struct sockaddr_in *src4, *dst4;

		src4 = (struct sockaddr_in *) cma_src_addr(id_priv);
		dst4 = (struct sockaddr_in *) cma_dst_addr(id_priv);

		cma_set_ip_ver(cma_hdr, 4);
		cma_hdr->src_addr.ip4.addr = src4->sin_addr.s_addr;
		cma_hdr->dst_addr.ip4.addr = dst4->sin_addr.s_addr;
		cma_hdr->port = src4->sin_port;
	} else if (cma_family(id_priv) == AF_INET6) {
		struct sockaddr_in6 *src6, *dst6;

		src6 = (struct sockaddr_in6 *) cma_src_addr(id_priv);
		dst6 = (struct sockaddr_in6 *) cma_dst_addr(id_priv);

		cma_set_ip_ver(cma_hdr, 6);
		cma_hdr->src_addr.ip6 = src6->sin6_addr;
		cma_hdr->dst_addr.ip6 = dst6->sin6_addr;
		cma_hdr->port = src6->sin6_port;
		cma_ip6_clear_scope_id(&cma_hdr->src_addr.ip6);
		cma_ip6_clear_scope_id(&cma_hdr->dst_addr.ip6);
	}
	return 0;
}