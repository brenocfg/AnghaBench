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
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
yes (void)
{
	char reply[256], *p;

	reply[sizeof(reply) - 1] = 0;
	for (;;) {
		fflush(stdout);
		if (!fgets (reply, sizeof(reply) - 1, stdin))
			return (0);
		for (p=reply; *p==' ' || *p=='\t'; ++p)
			continue;
		if (*p=='y' || *p=='Y')
			return (1);
		if (*p=='n' || *p=='N' || *p=='\n' || *p=='\r')
			return (0);
		printf("Answer `yes' or `no': ");
	}
}