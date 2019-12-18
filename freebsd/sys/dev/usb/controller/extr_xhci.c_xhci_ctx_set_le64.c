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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  uintptr_t uint32_t ;
struct xhci_softc {scalar_t__ sc_ctx_is_64_byte; } ;

/* Variables and functions */
 int XHCI_PAGE_SIZE ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xhci_ctx_set_le64(struct xhci_softc *sc, volatile uint64_t *ptr, uint64_t val)
{
	if (sc->sc_ctx_is_64_byte) {
		uint32_t offset;
		/* exploit the fact that our structures are XHCI_PAGE_SIZE aligned */
		/* all contexts are initially 32-bytes */
		offset = ((uintptr_t)ptr) & ((XHCI_PAGE_SIZE - 1) & ~(31U));
		ptr = (volatile uint64_t *)(((volatile uint8_t *)ptr) + offset);
	}
	*ptr = htole64(val);
}