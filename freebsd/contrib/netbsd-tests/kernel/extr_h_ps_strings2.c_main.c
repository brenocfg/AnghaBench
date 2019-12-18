#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char** ps_argvstr; size_t ps_nargvstr; } ;

/* Variables and functions */
 size_t LEN ; 
 int /*<<< orphan*/  UINT_MAX ; 
 TYPE_1__* __ps_strings ; 
 char** calloc (size_t,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 
 char* strdup (char*) ; 

int
main(void)
{
	size_t i;
	char buf[16];
	char **argv;

	if ((argv = calloc(LEN, sizeof(*argv))) == NULL)
		errx(1, "calloc failed");
	for (i = 0; i < LEN; ++i) {
		snprintf(buf, sizeof(buf), "arg%04zx", i);
		if ((argv[i] = strdup(buf)) == NULL)
			errx(1, "strdup failed");
	}
	__ps_strings->ps_argvstr = argv;
	__ps_strings->ps_nargvstr = LEN;

	printf("Sleeping forever...\n");
	do {
		sleep(UINT_MAX);
	} while /* CONSTCOND */ (1);
	return 0;
}