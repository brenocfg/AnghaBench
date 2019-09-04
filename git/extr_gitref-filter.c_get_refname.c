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
struct TYPE_2__ {int /*<<< orphan*/  refname; } ;
struct used_atom {TYPE_1__ u; } ;
struct ref_array_item {int kind; int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 int FILTER_REFS_DETACHED_HEAD ; 
 char const* get_head_description () ; 
 char const* show_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *get_refname(struct used_atom *atom, struct ref_array_item *ref)
{
	if (ref->kind & FILTER_REFS_DETACHED_HEAD)
		return get_head_description();
	return show_ref(&atom->u.refname, ref->refname);
}