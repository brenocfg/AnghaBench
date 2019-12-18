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
typedef  int /*<<< orphan*/  git_object_t ;
typedef  int git_filemode_t ;

/* Variables and functions */
#define  GIT_FILEMODE_COMMIT 129 
#define  GIT_FILEMODE_TREE 128 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 

__attribute__((used)) static git_object_t otype_from_mode(git_filemode_t filemode)
{
	switch (filemode) {
	case GIT_FILEMODE_TREE:
		return GIT_OBJECT_TREE;
	case GIT_FILEMODE_COMMIT:
		return GIT_OBJECT_COMMIT;
	default:
		return GIT_OBJECT_BLOB;
	}
}