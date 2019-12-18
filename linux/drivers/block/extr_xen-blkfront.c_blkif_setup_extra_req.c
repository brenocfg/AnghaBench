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
typedef  int uint16_t ;
struct TYPE_3__ {int nr_segments; int /*<<< orphan*/  handle; scalar_t__ sector_number; } ;
struct TYPE_4__ {TYPE_1__ rw; } ;
struct blkif_request {int /*<<< orphan*/  operation; TYPE_2__ u; } ;

/* Variables and functions */
 int BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
 int XEN_PAGE_SIZE ; 

__attribute__((used)) static void blkif_setup_extra_req(struct blkif_request *first,
				  struct blkif_request *second)
{
	uint16_t nr_segments = first->u.rw.nr_segments;

	/*
	 * The second request is only present when the first request uses
	 * all its segments. It's always the continuity of the first one.
	 */
	first->u.rw.nr_segments = BLKIF_MAX_SEGMENTS_PER_REQUEST;

	second->u.rw.nr_segments = nr_segments - BLKIF_MAX_SEGMENTS_PER_REQUEST;
	second->u.rw.sector_number = first->u.rw.sector_number +
		(BLKIF_MAX_SEGMENTS_PER_REQUEST * XEN_PAGE_SIZE) / 512;

	second->u.rw.handle = first->u.rw.handle;
	second->operation = first->operation;
}