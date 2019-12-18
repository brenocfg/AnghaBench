#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {scalar_t__ fb_size; int /*<<< orphan*/  fb_flags; scalar_t__ fb_pbase; } ;
struct ps3fb_softc {TYPE_1__ fb_info; int /*<<< orphan*/  sc_fbcontext; int /*<<< orphan*/  sc_reports_size; int /*<<< orphan*/  sc_reports; int /*<<< orphan*/  sc_driver_info; int /*<<< orphan*/  sc_dma_control; int /*<<< orphan*/  sc_fbhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_FLAG_NOWRITE ; 
 int /*<<< orphan*/  L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_FLIP ; 
 int /*<<< orphan*/  L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_MODE_SET ; 
 int /*<<< orphan*/  L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_SYNC ; 
 int /*<<< orphan*/  L1GPU_DISPLAY_SYNC_VSYNC ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  lv1_gpu_close () ; 
 int /*<<< orphan*/  lv1_gpu_context_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lv1_gpu_context_attribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_gpu_memory_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  lv1_gpu_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kenter_attr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ps3fb_softc ps3fb_softc ; 
 int /*<<< orphan*/  roundup2 (scalar_t__,int) ; 

void
ps3fb_remap(void)
{
	struct ps3fb_softc *sc;
	vm_offset_t va, fb_paddr;

	sc = &ps3fb_softc;

	lv1_gpu_close();
	lv1_gpu_open(0);

	lv1_gpu_context_attribute(0, L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_MODE_SET,
	    0,0,0,0);
	lv1_gpu_context_attribute(0, L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_MODE_SET,
	    0,0,1,0);
	lv1_gpu_context_attribute(0, L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_SYNC,
	    0,L1GPU_DISPLAY_SYNC_VSYNC,0,0);
	lv1_gpu_context_attribute(0, L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_SYNC,
	    1,L1GPU_DISPLAY_SYNC_VSYNC,0,0);
	lv1_gpu_memory_allocate(roundup2(sc->fb_info.fb_size, 1024*1024),
	    0, 0, 0, 0, &sc->sc_fbhandle, &fb_paddr);
	lv1_gpu_context_allocate(sc->sc_fbhandle, 0, &sc->sc_fbcontext,
	    &sc->sc_dma_control, &sc->sc_driver_info, &sc->sc_reports,
	    &sc->sc_reports_size);

	lv1_gpu_context_attribute(sc->sc_fbcontext,
	    L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_FLIP, 0, 0, 0, 0);
	lv1_gpu_context_attribute(sc->sc_fbcontext,
	    L1GPU_CONTEXT_ATTRIBUTE_DISPLAY_FLIP, 1, 0, 0, 0);

	sc->fb_info.fb_pbase = fb_paddr;
	for (va = 0; va < sc->fb_info.fb_size; va += PAGE_SIZE)
		pmap_kenter_attr(0x10000000 + va, fb_paddr + va,
		    VM_MEMATTR_WRITE_COMBINING);
	sc->fb_info.fb_flags &= ~FB_FLAG_NOWRITE;
}