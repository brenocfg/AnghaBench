#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct spglist {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _pmap_unwire_ptp (int /*<<< orphan*/ ,TYPE_1__*,struct spglist*) ; 

__attribute__((used)) static inline boolean_t
pmap_unwire_ptp(pmap_t pmap, vm_page_t m, struct spglist *free)
{

	--m->ref_count;
	if (m->ref_count == 0) {
		_pmap_unwire_ptp(pmap, m, free);
		return (TRUE);
	} else
		return (FALSE);
}