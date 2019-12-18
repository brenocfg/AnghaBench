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
struct TYPE_3__ {int hop_cnt; char* path; } ;
typedef  TYPE_1__ DRPath ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,...) ; 
 scalar_t__ atoi (char*) ; 
 char dev_port ; 
 char* strchr (char*,char) ; 

int str2DRPath(char *str, DRPath * path)
{
	char *s;

	path->hop_cnt = -1;

	DEBUG("DR str: %s", str);
	while (str && *str) {
		if ((s = strchr(str, ',')))
			*s = 0;
		path->path[++path->hop_cnt] = (char)atoi(str);
		if (!s)
			break;
		str = s + 1;
	}

#if 0
	if (path->path[0] != 0 ||
	    (path->hop_cnt > 0 && dev_port && path->path[1] != dev_port)) {
		DEBUG("hop 0 != 0 or hop 1 != dev_port");
		return -1;
	}
#endif

	return path->hop_cnt;
}