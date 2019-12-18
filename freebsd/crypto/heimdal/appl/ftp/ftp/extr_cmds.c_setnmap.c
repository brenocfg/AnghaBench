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
 int /*<<< orphan*/  MaxPathLen ; 
 char* altarg ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int mapflag ; 
 int /*<<< orphan*/  mapin ; 
 int /*<<< orphan*/  mapout ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ proxy ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
setnmap(int argc, char **argv)
{
	char *cp;

	if (argc == 1) {
		mapflag = 0;
		printf("Nmap off.\n");
		code = mapflag;
		return;
	}
	if (argc < 3 && !another(&argc, &argv, "mapout")) {
		printf("Usage: %s [mapin mapout]\n",argv[0]);
		code = -1;
		return;
	}
	mapflag = 1;
	code = 1;
	cp = strchr(altarg, ' ');
	if (cp == NULL) {
		printf("Usage: %s missing space\n",argv[0]);
		code = -1;
		return;
	}
	if (proxy) {
		while(*++cp == ' ')
			continue;
		altarg = cp;
		cp = strchr(altarg, ' ');
	}
	*cp = '\0';
	strlcpy(mapin, altarg, MaxPathLen);
	while (*++cp == ' ')
		continue;
	strlcpy(mapout, cp, MaxPathLen);
}