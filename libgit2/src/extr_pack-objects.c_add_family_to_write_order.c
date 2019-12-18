#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* delta; } ;
typedef  TYPE_1__ git_pobject ;

/* Variables and functions */
 int /*<<< orphan*/  add_descendants_to_write_order (TYPE_1__**,size_t*,TYPE_1__*) ; 

__attribute__((used)) static void add_family_to_write_order(git_pobject **wo, size_t *endp,
	git_pobject *po)
{
	git_pobject *root;

	for (root = po; root->delta; root = root->delta)
		; /* nothing */
	add_descendants_to_write_order(wo, endp, root);
}