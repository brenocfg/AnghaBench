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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; int /*<<< orphan*/ * path; int /*<<< orphan*/ * repo; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_filter_source ;
typedef  int /*<<< orphan*/  git_filter_mode_t ;
typedef  int /*<<< orphan*/  git_filter_list ;

/* Variables and functions */
 int filter_list_new (int /*<<< orphan*/ **,TYPE_1__*) ; 

int git_filter_list_new(
	git_filter_list **out,
	git_repository *repo,
	git_filter_mode_t mode,
	uint32_t flags)
{
	git_filter_source src = { 0 };
	src.repo = repo;
	src.path = NULL;
	src.mode = mode;
	src.flags = flags;
	return filter_list_new(out, &src);
}