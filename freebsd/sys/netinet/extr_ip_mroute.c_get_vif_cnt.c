#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vifi_t ;
struct sioc_vif_req {size_t vifi; int /*<<< orphan*/  obytes; int /*<<< orphan*/  ibytes; int /*<<< orphan*/  ocount; int /*<<< orphan*/  icount; } ;
struct TYPE_2__ {int /*<<< orphan*/  v_bytes_out; int /*<<< orphan*/  v_bytes_in; int /*<<< orphan*/  v_pkt_out; int /*<<< orphan*/  v_pkt_in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VIF_LOCK () ; 
 int /*<<< orphan*/  VIF_UNLOCK () ; 
 size_t V_numvifs ; 
 TYPE_1__* V_viftable ; 

__attribute__((used)) static int
get_vif_cnt(struct sioc_vif_req *req)
{
    vifi_t vifi = req->vifi;

    VIF_LOCK();
    if (vifi >= V_numvifs) {
	VIF_UNLOCK();
	return EINVAL;
    }

    req->icount = V_viftable[vifi].v_pkt_in;
    req->ocount = V_viftable[vifi].v_pkt_out;
    req->ibytes = V_viftable[vifi].v_bytes_in;
    req->obytes = V_viftable[vifi].v_bytes_out;
    VIF_UNLOCK();

    return 0;
}