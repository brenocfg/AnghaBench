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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct krping_rdma_info {void* size; void* rkey; int /*<<< orphan*/  buf; } ;
struct krping_cb {int /*<<< orphan*/  size; int /*<<< orphan*/  server_invalidate; scalar_t__ bw; scalar_t__ rlat; scalar_t__ wlat; int /*<<< orphan*/  server; struct krping_rdma_info send_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonll (scalar_t__) ; 
 int /*<<< orphan*/  krping_rdma_rkey (struct krping_cb*,scalar_t__,int) ; 

__attribute__((used)) static void krping_format_send(struct krping_cb *cb, u64 buf)
{
	struct krping_rdma_info *info = &cb->send_buf;
	u32 rkey;

	/*
	 * Client side will do reg or mw bind before
	 * advertising the rdma buffer.  Server side
	 * sends have no data.
	 */
	if (!cb->server || cb->wlat || cb->rlat || cb->bw) {
		rkey = krping_rdma_rkey(cb, buf, !cb->server_invalidate);
		info->buf = htonll(buf);
		info->rkey = htonl(rkey);
		info->size = htonl(cb->size);
		DEBUG_LOG("RDMA addr %llx rkey %x len %d\n",
			  (unsigned long long)buf, rkey, cb->size);
	}
}