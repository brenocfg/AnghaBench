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
struct rbuf_info {int /*<<< orphan*/  dmap; int /*<<< orphan*/  dmat; struct mbuf* mbuf; } ;
struct nicvf {int /*<<< orphan*/  dev; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 struct rbuf_info* GET_RBUF_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
nicvf_rb_ptr_to_mbuf(struct nicvf *nic, bus_addr_t rb_ptr)
{
	struct mbuf *mbuf;
	struct rbuf_info *rinfo;

	/* Get buffer start address and alignment offset */
	rinfo = GET_RBUF_INFO(PHYS_TO_DMAP(rb_ptr));

	/* Now retrieve mbuf to give to stack */
	mbuf = rinfo->mbuf;
	if (__predict_false(mbuf == NULL)) {
		panic("%s: Received packet fragment with NULL mbuf",
		    device_get_nameunit(nic->dev));
	}
	/*
	 * Clear the mbuf in the descriptor to indicate
	 * that this slot is processed and free to use.
	 */
	rinfo->mbuf = NULL;

	bus_dmamap_sync(rinfo->dmat, rinfo->dmap, BUS_DMASYNC_POSTREAD);
	bus_dmamap_unload(rinfo->dmat, rinfo->dmap);

	return (mbuf);
}