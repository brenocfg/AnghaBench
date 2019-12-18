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
 int COMPLETE ; 
 int CONTINUE ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int command (char*,char*) ; 
 int connected ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* getpass (char*) ; 
 int /*<<< orphan*/  getremoteinfo () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  ttyout ; 

void
user(int argc, char *argv[])
{
	char *password;
	char emptypass[] = "";
	int n, aflag = 0;

	if (argc == 0)
		goto usage;
	if (argc < 2)
		(void)another(&argc, &argv, "username");
	if (argc < 2 || argc > 4) {
 usage:
		UPRINTF("usage: %s username [password [account]]\n",
		    argv[0]);
		code = -1;
		return;
	}
	n = command("USER %s", argv[1]);
	if (n == CONTINUE) {
		if (argc < 3) {
			password = getpass("Password: ");
			if (password == NULL)
				password = emptypass;
		} else {
			password = argv[2];
		}
		n = command("PASS %s", password);
		memset(password, 0, strlen(password));
	}
	if (n == CONTINUE) {
		aflag++;
		if (argc < 4) {
			password = getpass("Account: ");
			if (password == NULL)
				password = emptypass;
		} else {
			password = argv[3];
		}
		n = command("ACCT %s", password);
		memset(password, 0, strlen(password));
	}
	if (n != COMPLETE) {
		fputs("Login failed.\n", ttyout);
		return;
	}
	if (!aflag && argc == 4) {
		password = argv[3];
		(void)command("ACCT %s", password);
		memset(password, 0, strlen(password));
	}
	connected = -1;
	getremoteinfo();
}