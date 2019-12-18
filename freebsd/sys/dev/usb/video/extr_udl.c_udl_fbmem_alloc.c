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
typedef  scalar_t__ uint32_t ;
struct udl_softc {scalar_t__ sc_fb_size; int /*<<< orphan*/  sc_fb_copy; int /*<<< orphan*/  sc_fb_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USB_DL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int /*<<< orphan*/  udl_buffer_alloc (scalar_t__) ; 
 scalar_t__ udl_get_fb_size (struct udl_softc*) ; 

__attribute__((used)) static void
udl_fbmem_alloc(struct udl_softc *sc)
{
	uint32_t size;

	size = udl_get_fb_size(sc);
	size = round_page(size);
	/* check for zero size */
	if (size == 0)
		size = PAGE_SIZE;
	/*
	 * It is assumed that allocations above PAGE_SIZE bytes will
	 * be PAGE_SIZE aligned for use with mmap()
	 */
	sc->sc_fb_addr = udl_buffer_alloc(size);
	sc->sc_fb_copy = malloc(size, M_USB_DL, M_WAITOK | M_ZERO);
	sc->sc_fb_size = size;
}