#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct vm_freelist {int /*<<< orphan*/  lcnt; int /*<<< orphan*/  pl; } ;
struct TYPE_5__ {int order; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listq ; 

__attribute__((used)) static void
vm_freelist_add(struct vm_freelist *fl, vm_page_t m, int order, int tail)
{

	m->order = order;
	if (tail)
		TAILQ_INSERT_TAIL(&fl[order].pl, m, listq);
	else
		TAILQ_INSERT_HEAD(&fl[order].pl, m, listq);
	fl[order].lcnt++;
}