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
struct object_id {int dummy; } ;

/* Variables and functions */
 int rev_list_insert_ref (void*,char const*,struct object_id const*) ; 

__attribute__((used)) static int rev_list_insert_ref_oid(const char *refname, const struct object_id *oid,
				   int flag, void *cb_data)
{
	return rev_list_insert_ref(cb_data, refname, oid);
}