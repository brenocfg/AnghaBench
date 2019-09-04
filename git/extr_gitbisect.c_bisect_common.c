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
struct rev_info {scalar_t__ tree_objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  mark_edges_uninteresting (struct rev_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 

__attribute__((used)) static void bisect_common(struct rev_info *revs)
{
	if (prepare_revision_walk(revs))
		die("revision walk setup failed");
	if (revs->tree_objects)
		mark_edges_uninteresting(revs, NULL, 0);
}