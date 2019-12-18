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
typedef  int /*<<< orphan*/  answer ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 

const char *
askuser(const char *dflt)
{
	static char answer[256];
	char *p;

	/* We can get recalled; if so, don't continue uselessly. */
	if (feof(stdin) || ferror(stdin)) {
		(void)fprintf(stderr, "\n");
		exit(1);
	}
	for (;;) {
		if (dflt)
			(void)fprintf(stderr, "Terminal type? [%s] ", dflt);
		else
			(void)fprintf(stderr, "Terminal type? ");
		(void)fflush(stderr);

		if (fgets(answer, sizeof(answer), stdin) == NULL) {
			if (dflt == NULL) {
				(void)fprintf(stderr, "\n");
				exit(1);
			}
			return (dflt);
		}

		if ((p = strchr(answer, '\n')))
			*p = '\0';
		if (answer[0])
			return (answer);
		if (dflt != NULL)
			return (dflt);
	}
}