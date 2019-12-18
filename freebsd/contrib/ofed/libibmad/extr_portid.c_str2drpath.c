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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int cnt; int drdlid; int drslid; scalar_t__* p; } ;
typedef  TYPE_1__ ib_dr_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,char*) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

int str2drpath(ib_dr_path_t * path, char *routepath, int drslid, int drdlid)
{
	char *s, *str;
	char *tmp;

	path->cnt = -1;

	if (!routepath || !(tmp = strdup(routepath)))
		goto Exit;

	DEBUG("DR str: %s", routepath);

	str = tmp;

	while (str && *str) {
		if ((s = strchr(str, ',')))
			*s = 0;
		path->p[++path->cnt] = (uint8_t) atoi(str);
		if (!s)
			break;
		str = s + 1;
	}
	free(tmp);

Exit:
	path->drdlid = drdlid ? drdlid : 0xffff;
	path->drslid = drslid ? drslid : 0xffff;

	return path->cnt;
}