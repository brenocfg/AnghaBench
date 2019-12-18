#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union descriptor {int /*<<< orphan*/  sd; } ;
struct soft_segment_descriptor {int member_4; int member_7; int /*<<< orphan*/  ssd_limit; int /*<<< orphan*/  ssd_base; int /*<<< orphan*/  ssd_type; scalar_t__ ssd_def32; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_9__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct bios_segments {TYPE_5__ args; TYPE_4__ util; TYPE_3__ data; TYPE_2__ code16; TYPE_1__ code32; } ;

/* Variables and functions */
 int BIOSARGS_FLAG ; 
 int BIOSCODE_FLAG ; 
 int BIOSDATA_FLAG ; 
 int BIOSUTIL_FLAG ; 
 size_t GBIOSARGS_SEL ; 
 size_t GBIOSCODE16_SEL ; 
 size_t GBIOSCODE32_SEL ; 
 size_t GBIOSDATA_SEL ; 
 size_t GBIOSUTIL_SEL ; 
 size_t NGDT ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDT_MEMERA ; 
 int /*<<< orphan*/  SDT_MEMRWA ; 
 int /*<<< orphan*/  cpuid ; 
 union descriptor* gdt ; 
 int /*<<< orphan*/  ssdtosd (struct soft_segment_descriptor*,int /*<<< orphan*/ *) ; 

void
set_bios_selectors(struct bios_segments *seg, int flags)
{
    struct soft_segment_descriptor ssd = {
	0,			/* segment base address (overwritten) */
	0,			/* length (overwritten) */
	SDT_MEMERA,		/* segment type (overwritten) */
	0,			/* priority level */
	1,			/* descriptor present */
	0, 0,
	1,			/* descriptor size (overwritten) */
	0			/* granularity == byte units */
    };
    union descriptor *p_gdt;

#ifdef SMP
    p_gdt = &gdt[PCPU_GET(cpuid) * NGDT];
#else
    p_gdt = gdt;
#endif
	
    ssd.ssd_base = seg->code32.base;
    ssd.ssd_limit = seg->code32.limit;
    ssdtosd(&ssd, &p_gdt[GBIOSCODE32_SEL].sd);

    ssd.ssd_def32 = 0;
    if (flags & BIOSCODE_FLAG) {
	ssd.ssd_base = seg->code16.base;
	ssd.ssd_limit = seg->code16.limit;
	ssdtosd(&ssd, &p_gdt[GBIOSCODE16_SEL].sd);
    }

    ssd.ssd_type = SDT_MEMRWA;
    if (flags & BIOSDATA_FLAG) {
	ssd.ssd_base = seg->data.base;
	ssd.ssd_limit = seg->data.limit;
	ssdtosd(&ssd, &p_gdt[GBIOSDATA_SEL].sd);
    }

    if (flags & BIOSUTIL_FLAG) {
	ssd.ssd_base = seg->util.base;
	ssd.ssd_limit = seg->util.limit;
	ssdtosd(&ssd, &p_gdt[GBIOSUTIL_SEL].sd);
    }

    if (flags & BIOSARGS_FLAG) {
	ssd.ssd_base = seg->args.base;
	ssd.ssd_limit = seg->args.limit;
	ssdtosd(&ssd, &p_gdt[GBIOSARGS_SEL].sd);
    }
}