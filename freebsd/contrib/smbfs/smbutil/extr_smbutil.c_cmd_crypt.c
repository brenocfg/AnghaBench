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
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getpass (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* smb_simplecrypt (int /*<<< orphan*/ *,char*) ; 

int
cmd_crypt(int argc, char *argv[])
{
	char *cp, *psw;
    
	if (argc < 2)
		psw = getpass("Password:");
	else
		psw = argv[1];
	cp = smb_simplecrypt(NULL, psw);
	if (cp == NULL)
		errx(EX_DATAERR, "out of memory");
	printf("%s\n", cp);
	free(cp);
	exit(0);
}