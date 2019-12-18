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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int repo_has_object_file_with_flags (struct repository*,struct object_id const*,int /*<<< orphan*/ ) ; 

int repo_has_object_file(struct repository *r,
			 const struct object_id *oid)
{
	return repo_has_object_file_with_flags(r, oid, 0);
}