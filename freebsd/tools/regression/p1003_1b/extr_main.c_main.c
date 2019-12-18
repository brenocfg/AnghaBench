#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* t; int (* f ) (int,char**) ;scalar_t__ works; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int stub1 (int,char**) ; 
 int stub2 (int,char**) ; 
 TYPE_1__* tab ; 
 int usage (int,char**) ; 

int main(int argc, char *argv[])
{
	int i;

	if (argc == 2 && strcmp(argv[1], "-a") == 0) {
#if 1
		fprintf(stderr,
			"-a should but doesn't really work"
			" (my notes say \"because things detach\");\n"
			"meanwhile do these individual tests and look"
			" for a non-zero exit code:\n");
		for (i = 0; i < nitems(tab); i++)
			if (tab[i].works)
				fprintf(stderr, "p1003_1b %s\n", tab[i].t);
		return -1;
#else
		{
			int r;
			for (i = 0; i < nitems(tab); i++) {
				if (tab[i].works) {
					if ( (r =
					(*tab[i].f)(argc - 1, argv + 1)) ) {
						fprintf(stderr,
						"%s failed\n", tab[i].t);
						return r;
					}
				}
			}
			return 0;
		}
#endif
	}
	
	if (argc > 1) {
		for (i = 0; i < nitems(tab); i++)
			if (strcmp(tab[i].t, argv[1]) == 0)
				return (*tab[i].f)(argc - 1, argv + 1);
	}

	return usage(argc, argv);
}