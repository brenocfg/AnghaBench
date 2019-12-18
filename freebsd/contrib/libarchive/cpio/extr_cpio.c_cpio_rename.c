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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static const char *
cpio_rename(const char *name)
{
	static char buff[1024];
	FILE *t;
	char *p, *ret;
#if defined(_WIN32) && !defined(__CYGWIN__)
	FILE *to;

	t = fopen("CONIN$", "r");
	if (t == NULL)
		return (name);
	to = fopen("CONOUT$", "w");
	if (to == NULL) {
		fclose(t);
		return (name);
	}
	fprintf(to, "%s (Enter/./(new name))? ", name);
	fclose(to);
#else
	t = fopen("/dev/tty", "r+");
	if (t == NULL)
		return (name);
	fprintf(t, "%s (Enter/./(new name))? ", name);
	fflush(t);
#endif

	p = fgets(buff, sizeof(buff), t);
	fclose(t);
	if (p == NULL)
		/* End-of-file is a blank line. */
		return (NULL);

	while (*p == ' ' || *p == '\t')
		++p;
	if (*p == '\n' || *p == '\0')
		/* Empty line. */
		return (NULL);
	if (*p == '.' && p[1] == '\n')
		/* Single period preserves original name. */
		return (name);
	ret = p;
	/* Trim the final newline. */
	while (*p != '\0' && *p != '\n')
		++p;
	/* Overwrite the final \n with a null character. */
	*p = '\0';
	return (ret);
}