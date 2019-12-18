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
struct lio_mbuf_free_info {int /*<<< orphan*/  mb; int /*<<< orphan*/  map; } ;
struct lio_instr_queue {int /*<<< orphan*/  txtag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 

void
lio_free_mbuf(struct lio_instr_queue *iq, struct lio_mbuf_free_info *finfo)
{

	bus_dmamap_sync(iq->txtag, finfo->map, BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(iq->txtag, finfo->map);
	m_freem(finfo->mb);
}