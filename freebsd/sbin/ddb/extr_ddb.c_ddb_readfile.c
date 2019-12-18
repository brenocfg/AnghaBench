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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int MAXARG ; 
 int /*<<< orphan*/  WHITESP ; 
 int /*<<< orphan*/  ddb_main (int,char**) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 size_t strcspn (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 size_t strspn (char*,int /*<<< orphan*/ ) ; 

void
ddb_readfile(char *filename)
{
	char    buf[BUFSIZ];
	FILE*	f;

	if ((f = fopen(filename, "r")) == NULL)
		err(EX_UNAVAILABLE, "fopen: %s", filename);

#define WHITESP		" \t"
#define MAXARG	 	2
	while (fgets(buf, BUFSIZ, f)) {
		int argc = 0;
		char *argv[MAXARG];
		size_t spn;

		spn = strlen(buf);
		if (buf[spn-1] == '\n')
			buf[spn-1] = '\0';

		spn = strspn(buf, WHITESP);
		argv[0] = buf + spn;
		if (*argv[0] == '#' || *argv[0] == '\0')
			continue;
		argc++;

		spn = strcspn(argv[0], WHITESP);
		argv[1] = argv[0] + spn + strspn(argv[0] + spn, WHITESP);
		argv[0][spn] = '\0';
		if (*argv[1] != '\0')
			argc++;

#ifdef DEBUG
		{
			int i;
			printf("argc = %d\n", argc);
			for (i = 0; i < argc; i++) {
				printf("arg[%d] = %s\n", i, argv[i]);
			}
		}
#endif
		ddb_main(argc, argv);
	}
	fclose(f);
}