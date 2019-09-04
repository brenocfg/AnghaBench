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
struct commit {int dummy; } ;

/* Variables and functions */
 struct commit* lookup_commit_reference_gently (struct repository*,struct object_id const*,int /*<<< orphan*/ ) ; 

struct commit *lookup_commit_reference(struct repository *r, const struct object_id *oid)
{
	return lookup_commit_reference_gently(r, oid, 0);
}