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
struct ref_iterator_vtable {int dummy; } ;
struct ref_iterator {int ordered; scalar_t__ flags; int /*<<< orphan*/ * oid; int /*<<< orphan*/ * refname; struct ref_iterator_vtable* vtable; } ;

/* Variables and functions */

void base_ref_iterator_init(struct ref_iterator *iter,
			    struct ref_iterator_vtable *vtable,
			    int ordered)
{
	iter->vtable = vtable;
	iter->ordered = !!ordered;
	iter->refname = NULL;
	iter->oid = NULL;
	iter->flags = 0;
}