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
 int /*<<< orphan*/  NetClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_encrypt_connect (scalar_t__) ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net ; 
 int /*<<< orphan*/  printf (char*) ; 
 int resettermname ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tninit () ; 
 int /*<<< orphan*/  toplevel ; 

__attribute__((used)) static int
bye(int argc, char **argv)
{
    if (connected) {
	shutdown(net, 2);
	printf("Connection closed.\r\n");
	NetClose(net);
	connected = 0;
	resettermname = 1;
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
	auth_encrypt_connect(connected);
#endif
	/* reset options */
	tninit();
    }
    if ((argc != 2) || (strcmp(argv[1], "fromquit") != 0))
	longjmp(toplevel, 1);
    return 0;	/* NOTREACHED */
}