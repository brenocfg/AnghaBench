#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  checksum; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_index_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_index__changed_relative_to(
	git_index *index, const git_oid *checksum)
{
	/* attempt to update index (ignoring errors) */
	if (git_index_read(index, false) < 0)
		git_error_clear();

	return !!git_oid_cmp(&index->checksum, checksum);
}