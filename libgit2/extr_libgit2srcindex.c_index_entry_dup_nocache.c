#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  INDEX_OWNER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_entry_cpy_nocache (TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ index_entry_create (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int index_entry_dup_nocache(
	git_index_entry **out,
	git_index *index,
	const git_index_entry *src)
{
	if (index_entry_create(out, INDEX_OWNER(index), src->path, NULL, false) < 0)
		return -1;

	index_entry_cpy_nocache(*out, src);
	return 0;
}