#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_mailmap ;
struct TYPE_3__ {int /*<<< orphan*/  author; } ;
typedef  TYPE_1__ git_commit ;

/* Variables and functions */
 int git_mailmap_resolve_signature (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int git_commit_author_with_mailmap(
	git_signature **out, const git_commit *commit, const git_mailmap *mailmap)
{
	return git_mailmap_resolve_signature(out, mailmap, commit->author);
}