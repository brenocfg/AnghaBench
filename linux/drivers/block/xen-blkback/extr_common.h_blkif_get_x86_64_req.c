#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {int /*<<< orphan*/ * indirect_grefs; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; int /*<<< orphan*/  nr_segments; int /*<<< orphan*/  indirect_op; } ;
struct TYPE_15__ {int /*<<< orphan*/  nr_sectors; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; int /*<<< orphan*/  flag; } ;
struct TYPE_13__ {int nr_segments; int /*<<< orphan*/ * seg; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; } ;
struct TYPE_11__ {TYPE_9__ other; TYPE_6__ indirect; TYPE_4__ discard; TYPE_2__ rw; } ;
struct blkif_x86_64_request {TYPE_10__ u; int /*<<< orphan*/  operation; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int /*<<< orphan*/ * indirect_grefs; int /*<<< orphan*/  nr_segments; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; int /*<<< orphan*/  indirect_op; } ;
struct TYPE_14__ {int /*<<< orphan*/  nr_sectors; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; int /*<<< orphan*/  flag; } ;
struct TYPE_12__ {int nr_segments; int /*<<< orphan*/ * seg; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; } ;
struct TYPE_19__ {TYPE_7__ other; TYPE_5__ indirect; TYPE_3__ discard; TYPE_1__ rw; } ;
struct blkif_request {int operation; TYPE_8__ u; } ;

/* Variables and functions */
 int BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
#define  BLKIF_OP_DISCARD 133 
#define  BLKIF_OP_FLUSH_DISKCACHE 132 
#define  BLKIF_OP_INDIRECT 131 
#define  BLKIF_OP_READ 130 
#define  BLKIF_OP_WRITE 129 
#define  BLKIF_OP_WRITE_BARRIER 128 
 int /*<<< orphan*/  INDIRECT_PAGES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_INDIRECT_PAGES ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void blkif_get_x86_64_req(struct blkif_request *dst,
					struct blkif_x86_64_request *src)
{
	int i, n = BLKIF_MAX_SEGMENTS_PER_REQUEST, j;
	dst->operation = READ_ONCE(src->operation);
	switch (dst->operation) {
	case BLKIF_OP_READ:
	case BLKIF_OP_WRITE:
	case BLKIF_OP_WRITE_BARRIER:
	case BLKIF_OP_FLUSH_DISKCACHE:
		dst->u.rw.nr_segments = src->u.rw.nr_segments;
		dst->u.rw.handle = src->u.rw.handle;
		dst->u.rw.id = src->u.rw.id;
		dst->u.rw.sector_number = src->u.rw.sector_number;
		barrier();
		if (n > dst->u.rw.nr_segments)
			n = dst->u.rw.nr_segments;
		for (i = 0; i < n; i++)
			dst->u.rw.seg[i] = src->u.rw.seg[i];
		break;
	case BLKIF_OP_DISCARD:
		dst->u.discard.flag = src->u.discard.flag;
		dst->u.discard.id = src->u.discard.id;
		dst->u.discard.sector_number = src->u.discard.sector_number;
		dst->u.discard.nr_sectors = src->u.discard.nr_sectors;
		break;
	case BLKIF_OP_INDIRECT:
		dst->u.indirect.indirect_op = src->u.indirect.indirect_op;
		dst->u.indirect.nr_segments = src->u.indirect.nr_segments;
		dst->u.indirect.handle = src->u.indirect.handle;
		dst->u.indirect.id = src->u.indirect.id;
		dst->u.indirect.sector_number = src->u.indirect.sector_number;
		barrier();
		j = min(MAX_INDIRECT_PAGES, INDIRECT_PAGES(dst->u.indirect.nr_segments));
		for (i = 0; i < j; i++)
			dst->u.indirect.indirect_grefs[i] =
				src->u.indirect.indirect_grefs[i];
		break;
	default:
		/*
		 * Don't know how to translate this op. Only get the
		 * ID so failure can be reported to the frontend.
		 */
		dst->u.other.id = src->u.other.id;
		break;
	}
}