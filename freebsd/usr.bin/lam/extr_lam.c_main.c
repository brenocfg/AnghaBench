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
struct openfile {int /*<<< orphan*/  sepstring; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 int caph_limit_stdio () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatherline (struct openfile*) ; 
 int /*<<< orphan*/  getargs (char**) ; 
 struct openfile* input ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  linep ; 
 int /*<<< orphan*/  morefiles ; 
 int /*<<< orphan*/  nofinalnl ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct	openfile *ip;

	if (argc == 1)
		usage();
	if (caph_limit_stdio() == -1)
		err(1, "unable to limit stdio");
	getargs(argv);
	if (!morefiles)
		usage();

	/*
	 * Cache NLS data, for strerror, for err(3), before entering capability
	 * mode.
	 */
	caph_cache_catpages();
	if (caph_enter() < 0)
		err(1, "unable to enter capability mode");

	for (;;) {
		linep = line;
		for (ip = input; ip->fp != NULL; ip++)
			linep = gatherline(ip);
		if (!morefiles)
			exit(0);
		fputs(line, stdout);
		fputs(ip->sepstring, stdout);
		if (!nofinalnl)
			putchar('\n');
	}
}