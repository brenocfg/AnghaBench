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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIZE (struct sockaddr*) ; 
 int /*<<< orphan*/  addrnames ; 
 int /*<<< orphan*/  bprintf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* routename (struct sockaddr*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
pmsg_addrs(char *cp, int addrs)
{
	struct sockaddr *sa;
	int i;

	if (addrs == 0) {
		(void) putchar('\n');
		return;
	}
	printf("\nsockaddrs: ");
	bprintf(stdout, addrs, addrnames);
	putchar('\n');
	for (i = 1; i; i <<= 1)
		if (i & addrs) {
			sa = (struct sockaddr *)cp;
			printf(" %s", routename(sa));
			cp += SA_SIZE(sa);
		}
	putchar('\n');
}