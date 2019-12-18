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
struct diff_options {int dummy; } ;

/* Variables and functions */
 int diff_tree_oid (int /*<<< orphan*/ *,struct object_id const*,char const*,struct diff_options*) ; 

int diff_root_tree_oid(const struct object_id *new_oid, const char *base, struct diff_options *opt)
{
	return diff_tree_oid(NULL, new_oid, base, opt);
}