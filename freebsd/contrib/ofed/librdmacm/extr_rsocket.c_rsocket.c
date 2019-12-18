#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rsocket {int udp_sock; int index; TYPE_5__* cm_id; } ;
struct TYPE_6__ {int sa_family; } ;
struct TYPE_7__ {TYPE_1__ src_addr; } ;
struct TYPE_8__ {TYPE_2__ addr; } ;
struct TYPE_10__ {TYPE_4__* channel; TYPE_3__ route; } ;
struct TYPE_9__ {int fd; } ;

/* Variables and functions */
 int AF_IB ; 
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  RDMA_PS_TCP ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int ds_init (struct rsocket*,int) ; 
 int rdma_create_id (int /*<<< orphan*/ *,TYPE_5__**,struct rsocket*,int /*<<< orphan*/ ) ; 
 struct rsocket* rs_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rs_configure () ; 
 int /*<<< orphan*/  rs_free (struct rsocket*) ; 
 int rs_insert (struct rsocket*,int) ; 

int rsocket(int domain, int type, int protocol)
{
	struct rsocket *rs;
	int index, ret;

	if ((domain != AF_INET && domain != AF_INET6 && domain != AF_IB) ||
	    ((type != SOCK_STREAM) && (type != SOCK_DGRAM)) ||
	    (type == SOCK_STREAM && protocol && protocol != IPPROTO_TCP) ||
	    (type == SOCK_DGRAM && protocol && protocol != IPPROTO_UDP))
		return ERR(ENOTSUP);

	rs_configure();
	rs = rs_alloc(NULL, type);
	if (!rs)
		return ERR(ENOMEM);

	if (type == SOCK_STREAM) {
		ret = rdma_create_id(NULL, &rs->cm_id, rs, RDMA_PS_TCP);
		if (ret)
			goto err;

		rs->cm_id->route.addr.src_addr.sa_family = domain;
		index = rs->cm_id->channel->fd;
	} else {
		ret = ds_init(rs, domain);
		if (ret)
			goto err;

		index = rs->udp_sock;
	}

	ret = rs_insert(rs, index);
	if (ret < 0)
		goto err;

	return rs->index;

err:
	rs_free(rs);
	return ret;
}