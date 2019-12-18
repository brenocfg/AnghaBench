#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bcnt; struct TYPE_5__* nextfs; } ;
typedef  TYPE_1__ FS ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 scalar_t__ blocksize ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  display () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exitval ; 
 TYPE_1__* fshead ; 
 int /*<<< orphan*/  newsyntax (int,char***) ; 
 int /*<<< orphan*/  next (char**) ; 
 int /*<<< orphan*/  oldsyntax (int,char***) ; 
 int /*<<< orphan*/  rewrite (TYPE_1__*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ size (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 

int
main(int argc, char *argv[])
{
	FS *tfs;
	char *p;

	(void)setlocale(LC_ALL, "");

	if (!(p = strrchr(argv[0], 'o')) || strcmp(p, "od"))
		newsyntax(argc, &argv);
	else
		oldsyntax(argc, &argv);

	/* figure out the data block size */
	for (blocksize = 0, tfs = fshead; tfs; tfs = tfs->nextfs) {
		tfs->bcnt = size(tfs);
		if (blocksize < tfs->bcnt)
			blocksize = tfs->bcnt;
	}
	/* rewrite the rules, do syntax checking */
	for (tfs = fshead; tfs; tfs = tfs->nextfs)
		rewrite(tfs);

	/*
	 * Cache NLS data, for strerror, for err(3), before entering capability
	 * mode.
	 */
	caph_cache_catpages();
	if (caph_limit_stdio() < 0)
		err(1, "capsicum");

	(void)next(argv);
	display();
	exit(exitval);
}