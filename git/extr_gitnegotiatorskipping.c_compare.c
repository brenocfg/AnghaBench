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
struct entry {int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 int compare_commits_by_commit_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int compare(const void *a_, const void *b_, void *unused)
{
	const struct entry *a = a_;
	const struct entry *b = b_;
	return compare_commits_by_commit_date(a->commit, b->commit, NULL);
}