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
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 char* altarg ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int mapflag ; 
 int /*<<< orphan*/  mapin ; 
 int /*<<< orphan*/  mapout ; 
 scalar_t__ proxy ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyout ; 

void
setnmap(int argc, char *argv[])
{
	char *cp;

	if (argc == 1) {
		mapflag = 0;
		fputs("Nmap off.\n", ttyout);
		code = mapflag;
		return;
	}
	if (argc == 0 ||
	    (argc < 3 && !another(&argc, &argv, "mapout")) || argc > 3) {
		UPRINTF("usage: %s [mapin mapout]\n", argv[0]);
		code = -1;
		return;
	}
	mapflag = 1;
	code = 1;
	cp = strchr(altarg, ' ');
	if (proxy) {
		while(*++cp == ' ')
			continue;
		altarg = cp;
		cp = strchr(altarg, ' ');
	}
	*cp = '\0';
	(void)strlcpy(mapin, altarg, MAXPATHLEN);
	while (*++cp == ' ')
		continue;
	(void)strlcpy(mapout, cp, MAXPATHLEN);
}