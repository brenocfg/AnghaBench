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

/* Variables and functions */
 int /*<<< orphan*/  PAGE_COPY ; 
 int /*<<< orphan*/  PAGE_NONE ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 int _PAGE_NO_EXEC ; 
 int _PAGE_NO_READ ; 
 int _PAGE_PRESENT ; 
 int _PAGE_WRITE ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int _page_cachable_default ; 
 scalar_t__ cpu_has_rixi ; 
 int /*<<< orphan*/ * protection_map ; 

__attribute__((used)) static inline void setup_protection_map(void)
{
	if (cpu_has_rixi) {
		protection_map[0]  = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_NO_READ);
		protection_map[1]  = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC);
		protection_map[2]  = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_NO_READ);
		protection_map[3]  = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC);
		protection_map[4]  = __pgprot(_page_cachable_default | _PAGE_PRESENT);
		protection_map[5]  = __pgprot(_page_cachable_default | _PAGE_PRESENT);
		protection_map[6]  = __pgprot(_page_cachable_default | _PAGE_PRESENT);
		protection_map[7]  = __pgprot(_page_cachable_default | _PAGE_PRESENT);

		protection_map[8]  = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_NO_READ);
		protection_map[9]  = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC);
		protection_map[10] = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_WRITE | _PAGE_NO_READ);
		protection_map[11] = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_NO_EXEC | _PAGE_WRITE);
		protection_map[12] = __pgprot(_page_cachable_default | _PAGE_PRESENT);
		protection_map[13] = __pgprot(_page_cachable_default | _PAGE_PRESENT);
		protection_map[14] = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_WRITE);
		protection_map[15] = __pgprot(_page_cachable_default | _PAGE_PRESENT | _PAGE_WRITE);

	} else {
		protection_map[0] = PAGE_NONE;
		protection_map[1] = PAGE_READONLY;
		protection_map[2] = PAGE_COPY;
		protection_map[3] = PAGE_COPY;
		protection_map[4] = PAGE_READONLY;
		protection_map[5] = PAGE_READONLY;
		protection_map[6] = PAGE_COPY;
		protection_map[7] = PAGE_COPY;
		protection_map[8] = PAGE_NONE;
		protection_map[9] = PAGE_READONLY;
		protection_map[10] = PAGE_SHARED;
		protection_map[11] = PAGE_SHARED;
		protection_map[12] = PAGE_READONLY;
		protection_map[13] = PAGE_READONLY;
		protection_map[14] = PAGE_SHARED;
		protection_map[15] = PAGE_SHARED;
	}
}