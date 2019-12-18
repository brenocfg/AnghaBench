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
typedef  int u_int ;
struct netmap_slot {int dummy; } ;
struct netmap_ring {int dummy; } ;
struct netmap_obj_params {int size; int num; } ;
struct netmap_mem_d {int dummy; } ;
struct netmap_if {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t NETMAP_BUF_POOL ; 
 size_t NETMAP_IF_POOL ; 
 int NETMAP_POOLS_NR ; 
 size_t NETMAP_RING_POOL ; 
 struct netmap_mem_d* _netmap_mem_private_new (int,struct netmap_obj_params*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  netmap_mem_global_ops ; 
 struct netmap_obj_params* netmap_min_priv_params ; 
 scalar_t__ netmap_verbose ; 
 int /*<<< orphan*/  nm_prinf (char*,int,int,int,int,int,int) ; 

struct netmap_mem_d *
netmap_mem_private_new(u_int txr, u_int txd, u_int rxr, u_int rxd,
		u_int extra_bufs, u_int npipes, int *perr)
{
	struct netmap_mem_d *d = NULL;
	struct netmap_obj_params p[NETMAP_POOLS_NR];
	int i;
	u_int v, maxd;
	/* account for the fake host rings */
	txr++;
	rxr++;

	/* copy the min values */
	for (i = 0; i < NETMAP_POOLS_NR; i++) {
		p[i] = netmap_min_priv_params[i];
	}

	/* possibly increase them to fit user request */
	v = sizeof(struct netmap_if) + sizeof(ssize_t) * (txr + rxr);
	if (p[NETMAP_IF_POOL].size < v)
		p[NETMAP_IF_POOL].size = v;
	v = 2 + 4 * npipes;
	if (p[NETMAP_IF_POOL].num < v)
		p[NETMAP_IF_POOL].num = v;
	maxd = (txd > rxd) ? txd : rxd;
	v = sizeof(struct netmap_ring) + sizeof(struct netmap_slot) * maxd;
	if (p[NETMAP_RING_POOL].size < v)
		p[NETMAP_RING_POOL].size = v;
	/* each pipe endpoint needs two tx rings (1 normal + 1 host, fake)
	 * and two rx rings (again, 1 normal and 1 fake host)
	 */
	v = txr + rxr + 8 * npipes;
	if (p[NETMAP_RING_POOL].num < v)
		p[NETMAP_RING_POOL].num = v;
	/* for each pipe we only need the buffers for the 4 "real" rings.
	 * On the other end, the pipe ring dimension may be different from
	 * the parent port ring dimension. As a compromise, we allocate twice the
	 * space actually needed if the pipe rings were the same size as the parent rings
	 */
	v = (4 * npipes + rxr) * rxd + (4 * npipes + txr) * txd + 2 + extra_bufs;
		/* the +2 is for the tx and rx fake buffers (indices 0 and 1) */
	if (p[NETMAP_BUF_POOL].num < v)
		p[NETMAP_BUF_POOL].num = v;

	if (netmap_verbose)
		nm_prinf("req if %d*%d ring %d*%d buf %d*%d",
			p[NETMAP_IF_POOL].num,
			p[NETMAP_IF_POOL].size,
			p[NETMAP_RING_POOL].num,
			p[NETMAP_RING_POOL].size,
			p[NETMAP_BUF_POOL].num,
			p[NETMAP_BUF_POOL].size);

	d = _netmap_mem_private_new(sizeof(*d), p, &netmap_mem_global_ops, perr);

	return d;
}