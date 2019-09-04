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
struct oidset {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ oidset_insert (struct oidset*,struct object_id const*) ; 
 int /*<<< orphan*/  show_ref (char*,struct object_id const*) ; 

__attribute__((used)) static void show_one_alternate_ref(const struct object_id *oid,
				   void *data)
{
	struct oidset *seen = data;

	if (oidset_insert(seen, oid))
		return;

	show_ref(".have", oid);
}