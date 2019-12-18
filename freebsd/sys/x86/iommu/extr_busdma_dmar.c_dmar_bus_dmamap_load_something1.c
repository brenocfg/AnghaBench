#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct dmar_map_entry {scalar_t__ end; int start; int /*<<< orphan*/  flags; } ;
struct dmar_map_entries_tailq {int dummy; } ;
struct dmar_domain {int dummy; } ;
struct dmar_ctx {struct dmar_domain* domain; } ;
struct bus_dmamap_dmar {struct dmar_map_entries_tailq map_entries; scalar_t__ cansleep; } ;
struct TYPE_5__ {int nsegments; scalar_t__ maxsegsz; int alignment; scalar_t__ lowaddr; int highaddr; scalar_t__ boundary; } ;
struct bus_dma_tag_dmar {TYPE_2__ common; struct dmar_ctx* ctx; TYPE_1__* segments; } ;
typedef  scalar_t__ dmar_gaddr_t ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_4__ {int ds_addr; scalar_t__ ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int BUS_DMA_NOWRITE ; 
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int DMAR_GM_CANSPLIT ; 
 int DMAR_GM_CANWAIT ; 
 int /*<<< orphan*/  DMAR_MAP_ENTRY_MAP ; 
 int DMAR_MAP_ENTRY_READ ; 
 int DMAR_MAP_ENTRY_WRITE ; 
 int DMAR_PAGE_MASK ; 
 int DMAR_PAGE_SIZE ; 
 int EFBIG ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct dmar_map_entries_tailq*,struct dmar_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmamap_link ; 
 int dmar_gas_map (struct dmar_domain*,TYPE_2__*,scalar_t__,int,int,int,int /*<<< orphan*/ *,struct dmar_map_entry**) ; 
 int dmar_test_boundary (int,scalar_t__,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int /*<<< orphan*/  trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  unroll_link ; 

__attribute__((used)) static int
dmar_bus_dmamap_load_something1(struct bus_dma_tag_dmar *tag,
    struct bus_dmamap_dmar *map, vm_page_t *ma, int offset, bus_size_t buflen,
    int flags, bus_dma_segment_t *segs, int *segp,
    struct dmar_map_entries_tailq *unroll_list)
{
	struct dmar_ctx *ctx;
	struct dmar_domain *domain;
	struct dmar_map_entry *entry;
	dmar_gaddr_t size;
	bus_size_t buflen1;
	int error, idx, gas_flags, seg;

	KASSERT(offset < DMAR_PAGE_SIZE, ("offset %d", offset));
	if (segs == NULL)
		segs = tag->segments;
	ctx = tag->ctx;
	domain = ctx->domain;
	seg = *segp;
	error = 0;
	idx = 0;
	while (buflen > 0) {
		seg++;
		if (seg >= tag->common.nsegments) {
			error = EFBIG;
			break;
		}
		buflen1 = buflen > tag->common.maxsegsz ?
		    tag->common.maxsegsz : buflen;
		size = round_page(offset + buflen1);

		/*
		 * (Too) optimistically allow split if there are more
		 * then one segments left.
		 */
		gas_flags = map->cansleep ? DMAR_GM_CANWAIT : 0;
		if (seg + 1 < tag->common.nsegments)
			gas_flags |= DMAR_GM_CANSPLIT;

		error = dmar_gas_map(domain, &tag->common, size, offset,
		    DMAR_MAP_ENTRY_READ |
		    ((flags & BUS_DMA_NOWRITE) == 0 ? DMAR_MAP_ENTRY_WRITE : 0),
		    gas_flags, ma + idx, &entry);
		if (error != 0)
			break;
		if ((gas_flags & DMAR_GM_CANSPLIT) != 0) {
			KASSERT(size >= entry->end - entry->start,
			    ("split increased entry size %jx %jx %jx",
			    (uintmax_t)size, (uintmax_t)entry->start,
			    (uintmax_t)entry->end));
			size = entry->end - entry->start;
			if (buflen1 > size)
				buflen1 = size;
		} else {
			KASSERT(entry->end - entry->start == size,
			    ("no split allowed %jx %jx %jx",
			    (uintmax_t)size, (uintmax_t)entry->start,
			    (uintmax_t)entry->end));
		}
		if (offset + buflen1 > size)
			buflen1 = size - offset;
		if (buflen1 > tag->common.maxsegsz)
			buflen1 = tag->common.maxsegsz;

		KASSERT(((entry->start + offset) & (tag->common.alignment - 1))
		    == 0,
		    ("alignment failed: ctx %p start 0x%jx offset %x "
		    "align 0x%jx", ctx, (uintmax_t)entry->start, offset,
		    (uintmax_t)tag->common.alignment));
		KASSERT(entry->end <= tag->common.lowaddr ||
		    entry->start >= tag->common.highaddr,
		    ("entry placement failed: ctx %p start 0x%jx end 0x%jx "
		    "lowaddr 0x%jx highaddr 0x%jx", ctx,
		    (uintmax_t)entry->start, (uintmax_t)entry->end,
		    (uintmax_t)tag->common.lowaddr,
		    (uintmax_t)tag->common.highaddr));
		KASSERT(dmar_test_boundary(entry->start + offset, buflen1,
		    tag->common.boundary),
		    ("boundary failed: ctx %p start 0x%jx end 0x%jx "
		    "boundary 0x%jx", ctx, (uintmax_t)entry->start,
		    (uintmax_t)entry->end, (uintmax_t)tag->common.boundary));
		KASSERT(buflen1 <= tag->common.maxsegsz,
		    ("segment too large: ctx %p start 0x%jx end 0x%jx "
		    "buflen1 0x%jx maxsegsz 0x%jx", ctx,
		    (uintmax_t)entry->start, (uintmax_t)entry->end,
		    (uintmax_t)buflen1, (uintmax_t)tag->common.maxsegsz));

		DMAR_DOMAIN_LOCK(domain);
		TAILQ_INSERT_TAIL(&map->map_entries, entry, dmamap_link);
		entry->flags |= DMAR_MAP_ENTRY_MAP;
		DMAR_DOMAIN_UNLOCK(domain);
		TAILQ_INSERT_TAIL(unroll_list, entry, unroll_link);

		segs[seg].ds_addr = entry->start + offset;
		segs[seg].ds_len = buflen1;

		idx += OFF_TO_IDX(trunc_page(offset + buflen1));
		offset += buflen1;
		offset &= DMAR_PAGE_MASK;
		buflen -= buflen1;
	}
	if (error == 0)
		*segp = seg;
	return (error);
}