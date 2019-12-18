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
typedef  int /*<<< orphan*/  template ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 char* getenv (char*) ; 
 char* mkdtemp (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	const char *base;
	const char *tmpdir;
	char template[PATH_MAX];
	int r;
	char *dir;

	if (argc != 2)
		usage();
	base = argv[1];

	if ((tmpdir = getenv("TMPDIR")) == NULL)
		tmpdir = "/tmp";
	r = snprintf(template, sizeof(template), "%s/%s", tmpdir, base);
	if (r < 0 || (size_t)r >= sizeof(template))
		fatal("template string too long");
	dir = mkdtemp(template);
	if (dir == NULL) {
		perror("mkdtemp");
		exit(1);
	}
	puts(dir);
	return 0;
}