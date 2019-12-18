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
 int PFKEY_EXTLEN (char*) ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  free (char*) ; 
 int nitems (char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** requests ; 
 char* setpolicy (char*) ; 
 int /*<<< orphan*/  test (char*,int /*<<< orphan*/ ) ; 

main()
{
	int i;
	char *buf;

	for (i = 0; i < nitems(requests); i++) {
		printf("* requests:[%s]\n", requests[i]);
		if ((buf = setpolicy(requests[i])) == NULL)
			continue;
		printf("\tsetlen:%d\n", PFKEY_EXTLEN(buf));

		printf("\tPF_INET:\n");
		test(buf, PF_INET);

		printf("\tPF_INET6:\n");
		test(buf, PF_INET6);
		free(buf);
	}
}