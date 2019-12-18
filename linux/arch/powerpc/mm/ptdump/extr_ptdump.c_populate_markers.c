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
struct TYPE_2__ {int /*<<< orphan*/  start_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXADDR_START ; 
 int /*<<< orphan*/  FIXADDR_TOP ; 
 int /*<<< orphan*/  H_VMEMMAP_START ; 
 int /*<<< orphan*/  IOREMAP_BASE ; 
 int /*<<< orphan*/  IOREMAP_END ; 
 int /*<<< orphan*/  IOREMAP_TOP ; 
 int /*<<< orphan*/  ISA_IO_BASE ; 
 int /*<<< orphan*/  ISA_IO_END ; 
 int /*<<< orphan*/  KASAN_SHADOW_END ; 
 int /*<<< orphan*/  KASAN_SHADOW_START ; 
 int /*<<< orphan*/  LAST_PKMAP ; 
 int /*<<< orphan*/  PAGE_OFFSET ; 
 int /*<<< orphan*/  PHB_IO_BASE ; 
 int /*<<< orphan*/  PHB_IO_END ; 
 int /*<<< orphan*/  PKMAP_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKMAP_BASE ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 int /*<<< orphan*/  VMEMMAP_BASE ; 
 TYPE_1__* address_markers ; 
 int /*<<< orphan*/  ioremap_bot ; 

__attribute__((used)) static void populate_markers(void)
{
	int i = 0;

	address_markers[i++].start_address = PAGE_OFFSET;
	address_markers[i++].start_address = VMALLOC_START;
	address_markers[i++].start_address = VMALLOC_END;
#ifdef CONFIG_PPC64
	address_markers[i++].start_address = ISA_IO_BASE;
	address_markers[i++].start_address = ISA_IO_END;
	address_markers[i++].start_address = PHB_IO_BASE;
	address_markers[i++].start_address = PHB_IO_END;
	address_markers[i++].start_address = IOREMAP_BASE;
	address_markers[i++].start_address = IOREMAP_END;
	/* What is the ifdef about? */
#ifdef CONFIG_PPC_BOOK3S_64
	address_markers[i++].start_address =  H_VMEMMAP_START;
#else
	address_markers[i++].start_address =  VMEMMAP_BASE;
#endif
#else /* !CONFIG_PPC64 */
	address_markers[i++].start_address = ioremap_bot;
	address_markers[i++].start_address = IOREMAP_TOP;
#ifdef CONFIG_HIGHMEM
	address_markers[i++].start_address = PKMAP_BASE;
	address_markers[i++].start_address = PKMAP_ADDR(LAST_PKMAP);
#endif
	address_markers[i++].start_address = FIXADDR_START;
	address_markers[i++].start_address = FIXADDR_TOP;
#ifdef CONFIG_KASAN
	address_markers[i++].start_address = KASAN_SHADOW_START;
	address_markers[i++].start_address = KASAN_SHADOW_END;
#endif
#endif /* CONFIG_PPC64 */
}