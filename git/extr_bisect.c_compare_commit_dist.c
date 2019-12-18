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
struct commit_dist {scalar_t__ distance; TYPE_2__* commit; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int compare_commit_dist(const void *a_, const void *b_)
{
	struct commit_dist *a, *b;

	a = (struct commit_dist *)a_;
	b = (struct commit_dist *)b_;
	if (a->distance != b->distance)
		return b->distance - a->distance; /* desc sort */
	return oidcmp(&a->commit->object.oid, &b->commit->object.oid);
}