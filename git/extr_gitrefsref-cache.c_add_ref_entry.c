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
struct ref_entry {int /*<<< orphan*/  name; } ;
struct ref_dir {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry_to_dir (struct ref_dir*,struct ref_entry*) ; 
 struct ref_dir* find_containing_dir (struct ref_dir*,int /*<<< orphan*/ ,int) ; 

int add_ref_entry(struct ref_dir *dir, struct ref_entry *ref)
{
	dir = find_containing_dir(dir, ref->name, 1);
	if (!dir)
		return -1;
	add_entry_to_dir(dir, ref);
	return 0;
}