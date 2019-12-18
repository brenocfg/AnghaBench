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
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeargv (char*) ; 
 int margc ; 
 char** margv ; 
 char* port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setpeer0 (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
setpeer(int argc, char *argv[])
{
	char	line[MAXLINE];

	if (argc < 2) {
		strcpy(line, "Connect ");
		printf("(to) ");
		fgets(&line[strlen(line)], sizeof line - strlen(line), stdin);
		makeargv(line);
		argc = margc;
		argv = margv;
	}
	if ((argc < 2) || (argc > 3)) {
		printf("usage: %s [host [port]]\n", argv[0]);
		return;
	}
	if (argc == 3) {
		port = argv[2];
		setpeer0(argv[1], argv[2]);
	} else
		setpeer0(argv[1], NULL);
}