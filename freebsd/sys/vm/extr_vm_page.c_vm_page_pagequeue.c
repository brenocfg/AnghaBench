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
typedef  TYPE_1__* vm_page_t ;
typedef  size_t uint8_t ;
struct vm_pagequeue {int dummy; } ;
struct TYPE_6__ {struct vm_pagequeue* vmd_pagequeues; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 size_t PQ_NONE ; 
 size_t atomic_load_8 (int /*<<< orphan*/ *) ; 
 TYPE_2__* vm_pagequeue_domain (TYPE_1__*) ; 

__attribute__((used)) static struct vm_pagequeue *
vm_page_pagequeue(vm_page_t m)
{

	uint8_t queue;

	if ((queue = atomic_load_8(&m->queue)) == PQ_NONE)
		return (NULL);
	return (&vm_pagequeue_domain(m)->vmd_pagequeues[queue]);
}