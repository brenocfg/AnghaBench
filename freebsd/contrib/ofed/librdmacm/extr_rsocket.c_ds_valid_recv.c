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
struct ibv_wc {scalar_t__ byte_len; int /*<<< orphan*/  wr_id; } ;
struct ibv_grh {int dummy; } ;
struct ds_qp {scalar_t__ rbuf; } ;
struct ds_header {int version; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ DS_IPV4_HDR_LEN ; 
 scalar_t__ DS_IPV6_HDR_LEN ; 
 scalar_t__ rs_wr_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_valid_recv(struct ds_qp *qp, struct ibv_wc *wc)
{
	struct ds_header *hdr;

	hdr = (struct ds_header *) (qp->rbuf + rs_wr_data(wc->wr_id));
	return ((wc->byte_len >= sizeof(struct ibv_grh) + DS_IPV4_HDR_LEN) &&
		((hdr->version == 4 && hdr->length == DS_IPV4_HDR_LEN) ||
		 (hdr->version == 6 && hdr->length == DS_IPV6_HDR_LEN)));
}