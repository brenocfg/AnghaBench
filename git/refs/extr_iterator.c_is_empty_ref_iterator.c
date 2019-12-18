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
struct ref_iterator {int /*<<< orphan*/ * vtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  empty_ref_iterator_vtable ; 

int is_empty_ref_iterator(struct ref_iterator *ref_iterator)
{
	return ref_iterator->vtable == &empty_ref_iterator_vtable;
}