#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct aac_sg_table {int SgCount; TYPE_1__* SgEntry; } ;
struct aac_sg_entry {int dummy; } ;
struct TYPE_6__ {int Size; } ;
struct aac_fib {TYPE_2__ Header; int /*<<< orphan*/ * data; } ;
struct aac_blockwrite {struct aac_sg_table SgMap; } ;
struct TYPE_7__ {scalar_t__ ds_addr; int /*<<< orphan*/  ds_len; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
struct TYPE_5__ {scalar_t__ SgAddress; int /*<<< orphan*/  SgByteCount; } ;

/* Variables and functions */
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 

__attribute__((used)) static void
aac_dump_map_sg(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct aac_fib *fib;
	struct aac_blockwrite *bw;
	struct aac_sg_table *sg;
	int i;

	fib = (struct aac_fib *)arg;
	bw = (struct aac_blockwrite *)&fib->data[0];
	sg = &bw->SgMap;

	if (sg != NULL) {
		sg->SgCount = nsegs;
		for (i = 0; i < nsegs; i++) {
			if (segs[i].ds_addr >= BUS_SPACE_MAXADDR_32BIT)
				return;
			sg->SgEntry[i].SgAddress = segs[i].ds_addr;
			sg->SgEntry[i].SgByteCount = segs[i].ds_len;
		}
		fib->Header.Size = nsegs * sizeof(struct aac_sg_entry);
	}
}