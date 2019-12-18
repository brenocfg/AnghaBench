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
struct sioc_sg_req {int pktcnt; int bytecnt; int wrong_if; int /*<<< orphan*/  grp; int /*<<< orphan*/  src; } ;
struct mfc {int mfc_pkt_cnt; int mfc_byte_cnt; int mfc_wrong_if; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  MFC_LOCK () ; 
 int /*<<< orphan*/  MFC_UNLOCK () ; 
 struct mfc* mfc_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_sg_cnt(struct sioc_sg_req *req)
{
    struct mfc *rt;

    MFC_LOCK();
    rt = mfc_find(&req->src, &req->grp);
    if (rt == NULL) {
	MFC_UNLOCK();
	req->pktcnt = req->bytecnt = req->wrong_if = 0xffffffff;
	return EADDRNOTAVAIL;
    }
    req->pktcnt = rt->mfc_pkt_cnt;
    req->bytecnt = rt->mfc_byte_cnt;
    req->wrong_if = rt->mfc_wrong_if;
    MFC_UNLOCK();
    return 0;
}