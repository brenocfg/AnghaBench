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
struct TYPE_3__ {int type; int /*<<< orphan*/  needle; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CPUINFO_BUFSIZE ; 
 int RBCFG_SOC_UNKNOWN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_1__* rbcfg_socs ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpuinfo_find_soc(void)
{
	FILE *fp;
	char temp[CPUINFO_BUFSIZE];
	char *haystack, *needle;
	int i, found = 0, soc_type = RBCFG_SOC_UNKNOWN;

	fp = fopen("/proc/cpuinfo", "r");
	if (!fp)
		goto end;

	/* first, extract the system type line */
	needle = "system type";
	while(fgets(temp, CPUINFO_BUFSIZE, fp)) {
		if (!strncmp(temp, needle, strlen(needle))) {
			found = 1;
			break;
		}
	}

	fclose(fp);

	/* failsafe in case cpuinfo format changes */
	if (!found)
		goto end;

	/* skip the field header */
	haystack = strchr(temp, ':');

	/* then, try to identify known SoC, stop at first match */
	for (i = 0; i < ARRAY_SIZE(rbcfg_socs); i++) {
		if ((strstr(haystack, rbcfg_socs[i].needle))) {
			soc_type = rbcfg_socs[i].type;
			break;
		}
	}

end:
	return soc_type;
}