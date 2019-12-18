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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fseek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
kernconfdump(const char *file)
{
	struct stat st;
	FILE *fp, *pp;
	int error, osz, r;
	unsigned int i, off, size, t1, t2, align;
	char *cmd, *o;

	r = open(file, O_RDONLY);
	if (r == -1)
		err(EXIT_FAILURE, "Couldn't open file '%s'", file);
	error = fstat(r, &st);
	if (error == -1)
		err(EXIT_FAILURE, "fstat() failed");
	if (S_ISDIR(st.st_mode))
		errx(EXIT_FAILURE, "'%s' is a directory", file);
	fp = fdopen(r, "r");
	if (fp == NULL)
		err(EXIT_FAILURE, "fdopen() failed");
	osz = 1024;
	o = calloc(1, osz);
	if (o == NULL)
		err(EXIT_FAILURE, "Couldn't allocate memory");
	/* ELF note section header. */
	asprintf(&cmd, "/usr/bin/elfdump -c %s | grep -A 8 kern_conf"
	    "| tail -5 | cut -d ' ' -f 2 | paste - - - - -", file);
	if (cmd == NULL)
		errx(EXIT_FAILURE, "asprintf() failed");
	pp = popen(cmd, "r");
	if (pp == NULL)
		errx(EXIT_FAILURE, "popen() failed");
	free(cmd);
	(void)fread(o, osz, 1, pp);
	pclose(pp);
	r = sscanf(o, "%d%d%d%d%d", &off, &size, &t1, &t2, &align);
	free(o);
	if (r != 5)
		errx(EXIT_FAILURE, "File %s doesn't contain configuration "
		    "file. Either unsupported, or not compiled with "
		    "INCLUDE_CONFIG_FILE", file);
	r = fseek(fp, off, SEEK_CUR);
	if (r != 0)
		err(EXIT_FAILURE, "fseek() failed");
	for (i = 0; i < size; i++) {
		r = fgetc(fp);
		if (r == EOF)
			break;
		if (r == '\0') {
			assert(i == size - 1 &&
			    ("\\0 found in the middle of a file"));
			break;
		}
		fputc(r, stdout);
	}
	fclose(fp);
}