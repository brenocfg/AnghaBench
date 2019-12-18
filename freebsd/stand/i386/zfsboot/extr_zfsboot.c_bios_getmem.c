#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct bios_smap {int dummy; } ;
struct TYPE_6__ {scalar_t__ type; int base; int length; } ;
struct TYPE_5__ {scalar_t__ ebx; int addr; int eax; int ecx; int edx; void* ctl; int /*<<< orphan*/  efl; int /*<<< orphan*/  edi; int /*<<< orphan*/  es; } ;

/* Variables and functions */
 int HEAP_MIN ; 
 int SMAP_SIG ; 
 scalar_t__ SMAP_TYPE_MEMORY ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 void* V86_FLAGS ; 
 int /*<<< orphan*/  VTOPOFF (TYPE_2__*) ; 
 int /*<<< orphan*/  VTOPSEG (TYPE_2__*) ; 
 int bios_basemem ; 
 int bios_extmem ; 
 int high_heap_base ; 
 int high_heap_size ; 
 TYPE_2__ smap ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static void
bios_getmem(void)
{
    uint64_t size;

    /* Parse system memory map */
    v86.ebx = 0;
    do {
	v86.ctl = V86_FLAGS;
	v86.addr = 0x15;		/* int 0x15 function 0xe820*/
	v86.eax = 0xe820;
	v86.ecx = sizeof(struct bios_smap);
	v86.edx = SMAP_SIG;
	v86.es = VTOPSEG(&smap);
	v86.edi = VTOPOFF(&smap);
	v86int();
	if (V86_CY(v86.efl) || (v86.eax != SMAP_SIG))
	    break;
	/* look for a low-memory segment that's large enough */
	if ((smap.type == SMAP_TYPE_MEMORY) && (smap.base == 0) &&
	    (smap.length >= (512 * 1024)))
	    bios_basemem = smap.length;
	/* look for the first segment in 'extended' memory */
	if ((smap.type == SMAP_TYPE_MEMORY) && (smap.base == 0x100000)) {
	    bios_extmem = smap.length;
	}

	/*
	 * Look for the largest segment in 'extended' memory beyond
	 * 1MB but below 4GB.
	 */
	if ((smap.type == SMAP_TYPE_MEMORY) && (smap.base > 0x100000) &&
	    (smap.base < 0x100000000ull)) {
	    size = smap.length;

	    /*
	     * If this segment crosses the 4GB boundary, truncate it.
	     */
	    if (smap.base + size > 0x100000000ull)
		size = 0x100000000ull - smap.base;

	    if (size > high_heap_size) {
		high_heap_size = size;
		high_heap_base = smap.base;
	    }
	}
    } while (v86.ebx != 0);

    /* Fall back to the old compatibility function for base memory */
    if (bios_basemem == 0) {
	v86.ctl = 0;
	v86.addr = 0x12;		/* int 0x12 */
	v86int();
	
	bios_basemem = (v86.eax & 0xffff) * 1024;
    }

    /* Fall back through several compatibility functions for extended memory */
    if (bios_extmem == 0) {
	v86.ctl = V86_FLAGS;
	v86.addr = 0x15;		/* int 0x15 function 0xe801*/
	v86.eax = 0xe801;
	v86int();
	if (!V86_CY(v86.efl)) {
	    bios_extmem = ((v86.ecx & 0xffff) + ((v86.edx & 0xffff) * 64)) * 1024;
	}
    }
    if (bios_extmem == 0) {
	v86.ctl = 0;
	v86.addr = 0x15;		/* int 0x15 function 0x88*/
	v86.eax = 0x8800;
	v86int();
	bios_extmem = (v86.eax & 0xffff) * 1024;
    }

    /*
     * If we have extended memory and did not find a suitable heap
     * region in the SMAP, use the last 3MB of 'extended' memory as a
     * high heap candidate.
     */
    if (bios_extmem >= HEAP_MIN && high_heap_size < HEAP_MIN) {
	high_heap_size = HEAP_MIN;
	high_heap_base = bios_extmem + 0x100000 - HEAP_MIN;
    }
}