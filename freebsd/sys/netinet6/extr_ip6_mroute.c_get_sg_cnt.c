#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct sioc_sg_req6 {int /*<<< orphan*/  wrong_if; int /*<<< orphan*/  bytecnt; int /*<<< orphan*/  pktcnt; TYPE_2__ grp; TYPE_1__ src; } ;
struct mf6c {int /*<<< orphan*/  mf6c_wrong_if; int /*<<< orphan*/  mf6c_byte_cnt; int /*<<< orphan*/  mf6c_pkt_cnt; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  MF6CFIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mf6c*) ; 
 int /*<<< orphan*/  MFC6_LOCK () ; 
 int /*<<< orphan*/  MFC6_UNLOCK () ; 

__attribute__((used)) static int
get_sg_cnt(struct sioc_sg_req6 *req)
{
	struct mf6c *rt;
	int ret;

	ret = 0;

	MFC6_LOCK();

	MF6CFIND(req->src.sin6_addr, req->grp.sin6_addr, rt);
	if (rt == NULL) {
		ret = ESRCH;
	} else {
		req->pktcnt = rt->mf6c_pkt_cnt;
		req->bytecnt = rt->mf6c_byte_cnt;
		req->wrong_if = rt->mf6c_wrong_if;
	}

	MFC6_UNLOCK();

	return (ret);
}