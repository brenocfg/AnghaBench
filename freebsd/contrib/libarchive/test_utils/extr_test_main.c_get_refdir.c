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
 int /*<<< orphan*/  DebugBreak () ; 
 char* KNOWNREF ; 
 char* LIBRARY ; 
 size_t PATH_MAX ; 
 char* PROGRAM ; 
 char* PROGRAM_ALIAS ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* slurpfile (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,size_t) ; 

__attribute__((used)) static char *
get_refdir(const char *d)
{
	size_t tried_size, buff_size;
	char *buff, *tried, *pwd = NULL, *p = NULL;

#ifdef PATH_MAX
	buff_size = PATH_MAX;
#else
	buff_size = 8192;
#endif
	buff = calloc(buff_size, 1);
	if (buff == NULL) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	/* Allocate a buffer to hold the various directories we checked. */
	tried_size = buff_size * 2;
	tried = calloc(tried_size, 1);
	if (tried == NULL) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	/* If a dir was specified, try that */
	if (d != NULL) {
		pwd = NULL;
		snprintf(buff, buff_size, "%s", d);
		p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
		if (p != NULL) goto success;
		strncat(tried, buff, tried_size - strlen(tried) - 1);
		strncat(tried, "\n", tried_size - strlen(tried) - 1);
		goto failure;
	}

	/* Get the current dir. */
#ifdef PATH_MAX
	pwd = getcwd(NULL, PATH_MAX);/* Solaris getcwd needs the size. */
#else
	pwd = getcwd(NULL, 0);
#endif
	while (pwd[strlen(pwd) - 1] == '\n')
		pwd[strlen(pwd) - 1] = '\0';

	/* Look for a known file. */
	snprintf(buff, buff_size, "%s", pwd);
	p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
	if (p != NULL) goto success;
	strncat(tried, buff, tried_size - strlen(tried) - 1);
	strncat(tried, "\n", tried_size - strlen(tried) - 1);

	snprintf(buff, buff_size, "%s/test", pwd);
	p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
	if (p != NULL) goto success;
	strncat(tried, buff, tried_size - strlen(tried) - 1);
	strncat(tried, "\n", tried_size - strlen(tried) - 1);

#if defined(LIBRARY)
	snprintf(buff, buff_size, "%s/%s/test", pwd, LIBRARY);
#else
	snprintf(buff, buff_size, "%s/%s/test", pwd, PROGRAM);
#endif
	p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
	if (p != NULL) goto success;
	strncat(tried, buff, tried_size - strlen(tried) - 1);
	strncat(tried, "\n", tried_size - strlen(tried) - 1);

#if defined(PROGRAM_ALIAS)
	snprintf(buff, buff_size, "%s/%s/test", pwd, PROGRAM_ALIAS);
	p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
	if (p != NULL) goto success;
	strncat(tried, buff, tried_size - strlen(tried) - 1);
	strncat(tried, "\n", tried_size - strlen(tried) - 1);
#endif

	if (memcmp(pwd, "/usr/obj", 8) == 0) {
		snprintf(buff, buff_size, "%s", pwd + 8);
		p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
		if (p != NULL) goto success;
		strncat(tried, buff, tried_size - strlen(tried) - 1);
		strncat(tried, "\n", tried_size - strlen(tried) - 1);

		snprintf(buff, buff_size, "%s/test", pwd + 8);
		p = slurpfile(NULL, "%s/%s", buff, KNOWNREF);
		if (p != NULL) goto success;
		strncat(tried, buff, tried_size - strlen(tried) - 1);
		strncat(tried, "\n", tried_size - strlen(tried) - 1);
	}

failure:
	printf("Unable to locate known reference file %s\n", KNOWNREF);
	printf("  Checked following directories:\n%s\n", tried);
	printf("Use -r option to specify full path to reference directory\n");
#if defined(_WIN32) && !defined(__CYGWIN__) && defined(_DEBUG)
	DebugBreak();
#endif
	exit(1);

success:
	free(p);
	free(pwd);
	free(tried);

	/* Copy result into a fresh buffer to reduce memory usage. */
	p = strdup(buff);
	free(buff);
	return p;
}