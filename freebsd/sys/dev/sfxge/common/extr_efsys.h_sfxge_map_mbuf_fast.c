#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int /*<<< orphan*/  m_len; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_4__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_load_mbuf_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_offset_t ; 

__attribute__((used)) static __inline void
sfxge_map_mbuf_fast(bus_dma_tag_t tag, bus_dmamap_t map,
		    struct mbuf *m, bus_dma_segment_t *seg)
{
#if defined(__i386__) || defined(__amd64__)
	seg->ds_addr = pmap_kextract(mtod(m, vm_offset_t));
	seg->ds_len = m->m_len;
#else
	int nsegstmp;

	bus_dmamap_load_mbuf_sg(tag, map, m, seg, &nsegstmp, 0);
#endif
}