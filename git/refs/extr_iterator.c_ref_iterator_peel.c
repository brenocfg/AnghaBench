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
struct ref_iterator {TYPE_1__* vtable; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int (* peel ) (struct ref_iterator*,struct object_id*) ;} ;

/* Variables and functions */
 int stub1 (struct ref_iterator*,struct object_id*) ; 

int ref_iterator_peel(struct ref_iterator *ref_iterator,
		      struct object_id *peeled)
{
	return ref_iterator->vtable->peel(ref_iterator, peeled);
}