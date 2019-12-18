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
 int /*<<< orphan*/  free (struct ref_iterator*) ; 

void base_ref_iterator_free(struct ref_iterator *iter)
{
	/* Help make use-after-free bugs fail quickly: */
	iter->vtable = NULL;
	free(iter);
}