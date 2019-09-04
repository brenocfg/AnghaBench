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
struct TYPE_2__ {int (* advance ) (struct ref_iterator*) ;} ;

/* Variables and functions */
 int stub1 (struct ref_iterator*) ; 

int ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	return ref_iterator->vtable->advance(ref_iterator);
}