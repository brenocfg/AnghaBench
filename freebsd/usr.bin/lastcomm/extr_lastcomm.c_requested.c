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
struct acctv3 {int /*<<< orphan*/  ac_comm; int /*<<< orphan*/  ac_tty; int /*<<< orphan*/  ac_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_COMM_LEN ; 
 char* getdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* user_from_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
requested(char *argv[], struct acctv3 *acp)
{
	const char *p;

	do {
		p = user_from_uid(acp->ac_uid, 0);
		if (!strcmp(p, *argv))
			return (1);
		if ((p = getdev(acp->ac_tty)) && !strcmp(p, *argv))
			return (1);
		if (!strncmp(acp->ac_comm, *argv, AC_COMM_LEN))
			return (1);
	} while (*++argv);
	return (0);
}