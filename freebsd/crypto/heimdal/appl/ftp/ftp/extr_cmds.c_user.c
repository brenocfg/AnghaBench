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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  acctstr ;

/* Variables and functions */
 int COMPLETE ; 
 int CONTINUE ; 
 int /*<<< orphan*/  UI_UTIL_read_pw_string (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int command (char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 size_t strcspn (char*,char*) ; 

void
user(int argc, char **argv)
{
	char acctstr[80];
	int n, aflag = 0;
	char tmp[256];

	if (argc < 2)
		another(&argc, &argv, "username");
	if (argc < 2 || argc > 4) {
		printf("usage: %s username [password] [account]\n", argv[0]);
		code = -1;
		return;
	}
	n = command("USER %s", argv[1]);
	if (n == CONTINUE) {
	    if (argc < 3 ) {
		UI_UTIL_read_pw_string (tmp,
				    sizeof(tmp),
				    "Password: ", 0);
		argv[2] = tmp;
		argc++;
	    }
	    n = command("PASS %s", argv[2]);
	}
	if (n == CONTINUE) {
		if (argc < 4) {
			printf("Account: "); fflush(stdout);
			fgets(acctstr, sizeof(acctstr) - 1, stdin);
			acctstr[strcspn(acctstr, "\r\n")] = '\0';
			argv[3] = acctstr; argc++;
		}
		n = command("ACCT %s", argv[3]);
		aflag++;
	}
	if (n != COMPLETE) {
		fprintf(stdout, "Login failed.\n");
		return;
	}
	if (!aflag && argc == 4) {
		command("ACCT %s", argv[3]);
	}
}