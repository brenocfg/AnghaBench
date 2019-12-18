#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_4__ {int /*<<< orphan*/  pv_list; scalar_t__ pv_tracked; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mmu_booke_page_init(mmu_t mmu, vm_page_t m)
{

	m->md.pv_tracked = 0;
	TAILQ_INIT(&m->md.pv_list);
}