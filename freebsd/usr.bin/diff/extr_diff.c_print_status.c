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

/* Variables and functions */
#define  D_BINARY 134 
 int /*<<< orphan*/  D_BRIEF ; 
#define  D_DIFFER 133 
#define  D_MISMATCH1 132 
#define  D_MISMATCH2 131 
#define  D_SAME 130 
#define  D_SKIPPED1 129 
#define  D_SKIPPED2 128 
 int /*<<< orphan*/  diff_format ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  sflag ; 

void
print_status(int val, char *path1, char *path2, const char *entry)
{
	switch (val) {
	case D_BINARY:
		printf("Binary files %s%s and %s%s differ\n",
		    path1, entry, path2, entry);
		break;
	case D_DIFFER:
		if (diff_format == D_BRIEF)
			printf("Files %s%s and %s%s differ\n",
			    path1, entry, path2, entry);
		break;
	case D_SAME:
		if (sflag)
			printf("Files %s%s and %s%s are identical\n",
			    path1, entry, path2, entry);
		break;
	case D_MISMATCH1:
		printf("File %s%s is a directory while file %s%s is a regular file\n",
		    path1, entry, path2, entry);
		break;
	case D_MISMATCH2:
		printf("File %s%s is a regular file while file %s%s is a directory\n",
		    path1, entry, path2, entry);
		break;
	case D_SKIPPED1:
		printf("File %s%s is not a regular file or directory and was skipped\n",
		    path1, entry);
		break;
	case D_SKIPPED2:
		printf("File %s%s is not a regular file or directory and was skipped\n",
		    path2, entry);
		break;
	}
}