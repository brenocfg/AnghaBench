#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {struct object_id oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 TYPE_2__* get_commit_tree (struct commit const*) ; 

struct object_id *get_commit_tree_oid(const struct commit *commit)
{
	return &get_commit_tree(commit)->object.oid;
}