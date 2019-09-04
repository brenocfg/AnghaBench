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
typedef  int /*<<< orphan*/  git_merge_file_options ;
struct TYPE_4__ {int /*<<< orphan*/  const* file_opts; } ;
typedef  TYPE_1__ git_merge_driver_source ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

const git_merge_file_options* git_merge_driver_source_file_options(const git_merge_driver_source *src)
{
	assert(src);
	return src->file_opts;
}