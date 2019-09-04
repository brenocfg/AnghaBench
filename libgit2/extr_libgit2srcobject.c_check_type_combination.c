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
typedef  int git_object_t ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int GIT_OBJECT_ANY ; 
#define  GIT_OBJECT_BLOB 131 
#define  GIT_OBJECT_COMMIT 130 
#define  GIT_OBJECT_TAG 129 
#define  GIT_OBJECT_TREE 128 

__attribute__((used)) static int check_type_combination(git_object_t type, git_object_t target)
{
	if (type == target)
		return 0;

	switch (type) {
	case GIT_OBJECT_BLOB:
	case GIT_OBJECT_TREE:
		/* a blob or tree can never be peeled to anything but themselves */
		return GIT_EINVALIDSPEC;
		break;
	case GIT_OBJECT_COMMIT:
		/* a commit can only be peeled to a tree */
		if (target != GIT_OBJECT_TREE && target != GIT_OBJECT_ANY)
			return GIT_EINVALIDSPEC;
		break;
	case GIT_OBJECT_TAG:
		/* a tag may point to anything, so we let anything through */
		break;
	default:
		return GIT_EINVALIDSPEC;
	}

	return 0;
}