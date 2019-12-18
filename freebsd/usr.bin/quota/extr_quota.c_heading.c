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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char const*,...) ; 
 char** qfextension ; 
 int /*<<< orphan*/  qflag ; 

__attribute__((used)) static void
heading(int type, u_long id, const char *name, const char *tag)
{

	printf("Disk quotas for %s %s (%cid %lu): %s\n", qfextension[type],
	    name, *qfextension[type], id, tag);
	if (!qflag && tag[0] == '\0') {
		printf("%-15s %7s %8s %7s %7s %6s %7s %6s%8s\n"
			, "Filesystem"
			, "usage"
			, "quota"
			, "limit"
			, "grace"
			, "files"
			, "quota"
			, "limit"
			, "grace"
		);
	}
}