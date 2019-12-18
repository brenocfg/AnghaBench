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
typedef  int /*<<< orphan*/ * vm_page_t ;
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_current_npages; } ;

/* Variables and functions */
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int /*<<< orphan*/ * vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static vm_page_t
vtballoon_alloc_page(struct vtballoon_softc *sc)
{
	vm_page_t m;

	m = vm_page_alloc(NULL, 0, VM_ALLOC_NORMAL | VM_ALLOC_NOOBJ);
	if (m != NULL)
		sc->vtballoon_current_npages++;

	return (m);
}