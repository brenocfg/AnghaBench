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
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* progname ; 
 char** realloc (char**,int) ; 
 int spawn (char*,char**) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* stringf (char*,...) ; 
 char* strsave (char*) ; 
 int verbose ; 

__attribute__((used)) static int callsys(char **av) {
	int i, status = 0;
	static char **argv;
	static int argc;
	char *executable;

	for (i = 0; av[i] != NULL; i++)
		;
	if (i + 1 > argc) {
		argc = i + 1;
		if (argv == NULL)
			argv = malloc(argc*sizeof *argv);
		else
			argv = realloc(argv, argc*sizeof *argv);
		assert(argv);
	}
	for (i = 0; status == 0 && av[i] != NULL; ) {
		int j = 0;
		char *s = NULL;
		for ( ; av[i] != NULL && (s = strchr(av[i], '\n')) == NULL; i++)
			argv[j++] = av[i];
		if (s != NULL) {
			if (s > av[i])
				argv[j++] = stringf("%.*s", s - av[i], av[i]);
			if (s[1] != '\0')
				av[i] = s + 1;
			else
				i++;
		}
		argv[j] = NULL;
		executable = strsave( argv[0] );
		argv[0] = stringf( "\"%s\"", argv[0] );
		if (verbose > 0) {
			int k;
			fprintf(stderr, "%s", argv[0]);
			for (k = 1; argv[k] != NULL; k++)
				fprintf(stderr, " %s", argv[k]);
			fprintf(stderr, "\n");
		}
		if (verbose < 2)
			status = spawn(executable, argv);
		if (status == -1) {
			fprintf(stderr, "%s: ", progname);
			perror(argv[0]);
		}
	}
	return status;
}