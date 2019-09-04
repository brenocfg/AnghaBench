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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_attr_file_source ;

/* Variables and functions */
#define  GIT_ATTR_CHECK_FILE_THEN_INDEX 130 
#define  GIT_ATTR_CHECK_INDEX_ONLY 129 
#define  GIT_ATTR_CHECK_INDEX_THEN_FILE 128 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_INDEX ; 

__attribute__((used)) static int attr_decide_sources(
	uint32_t flags, bool has_wd, bool has_index, git_attr_file_source *srcs)
{
	int count = 0;

	switch (flags & 0x03) {
	case GIT_ATTR_CHECK_FILE_THEN_INDEX:
		if (has_wd)
			srcs[count++] = GIT_ATTR_FILE__FROM_FILE;
		if (has_index)
			srcs[count++] = GIT_ATTR_FILE__FROM_INDEX;
		break;
	case GIT_ATTR_CHECK_INDEX_THEN_FILE:
		if (has_index)
			srcs[count++] = GIT_ATTR_FILE__FROM_INDEX;
		if (has_wd)
			srcs[count++] = GIT_ATTR_FILE__FROM_FILE;
		break;
	case GIT_ATTR_CHECK_INDEX_ONLY:
		if (has_index)
			srcs[count++] = GIT_ATTR_FILE__FROM_INDEX;
		break;
	}

	return count;
}