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
 int code ; 
 int /*<<< orphan*/  confirm (char*,char*) ; 
 int /*<<< orphan*/  globulize (char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  recvrequest (char*,char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
ls(int argc, char **argv)
{
	char *cmd;

	if (argc < 2)
		argc++, argv[1] = NULL;
	if (argc < 3)
		argc++, argv[2] = "-";
	if (argc > 3) {
		printf("usage: %s remote-directory local-file\n", argv[0]);
		code = -1;
		return;
	}
	cmd = argv[0][0] == 'n' ? "NLST" : "LIST";
	if (strcmp(argv[2], "-") && !globulize(&argv[2])) {
		code = -1;
		return;
	}
	if (strcmp(argv[2], "-") && *argv[2] != '|')
	    if (!globulize(&argv[2]) || !confirm("output to local-file:",
						 argv[2])) {
		code = -1;
		return;
	    }
	recvrequest(cmd, argv[2], argv[1], "w", 0, 1);
}