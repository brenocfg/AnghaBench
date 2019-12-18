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
 int MAXLINE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeargv (char*) ; 
 int margc ; 
 char** margv ; 
 int /*<<< orphan*/  maxtimeouts ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  settimeouts (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  timeoutnetwork ; 

__attribute__((used)) static void
settimeoutpacket(int argc, char *argv[])
{
	int t;
	char	line[MAXLINE];

	if (argc < 2) {
		strcpy(line, "Packet timeout ");
		printf("(value) ");
		fgets(&line[strlen(line)], sizeof line - strlen(line), stdin);
		makeargv(line);
		argc = margc;
		argv = margv;
	}
	if (argc != 2) {
		printf("usage: %s value\n", argv[0]);
		return;
	}
	t = atoi(argv[1]);
	if (t < 0) {
		printf("%s: bad value\n", argv[1]);
		return;
	}

	settimeouts(t, timeoutnetwork, maxtimeouts);
}