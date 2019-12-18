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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fsnode ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ NODE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEBUG_APPLY_SPECFILE ; 
 scalar_t__ EOF ; 
 scalar_t__ F_DIR ; 
 int /*<<< orphan*/  TIMER_RESULTS (struct timeval,char*) ; 
 int /*<<< orphan*/  TIMER_START (struct timeval) ; 
 int /*<<< orphan*/  apply_specdir (char const*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free_nodes (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* spec (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void
apply_specfile(const char *specfile, const char *dir, fsnode *parent, int speconly)
{
	struct timeval	 start;
	FILE	*fp;
	NODE	*root;

	assert(specfile != NULL);
	assert(parent != NULL);

	if (debug & DEBUG_APPLY_SPECFILE)
		printf("apply_specfile: %s, %s %p\n", specfile, dir, parent);

				/* read in the specfile */
	if ((fp = fopen(specfile, "r")) == NULL)
		err(1, "Can't open `%s'", specfile);
	TIMER_START(start);
	root = spec(fp);
	TIMER_RESULTS(start, "spec");
	if (fclose(fp) == EOF)
		err(1, "Can't close `%s'", specfile);

				/* perform some sanity checks */
	if (root == NULL)
		errx(1, "Specfile `%s' did not contain a tree", specfile);
	assert(strcmp(root->name, ".") == 0);
	assert(root->type == F_DIR);

				/* merge in the changes */
	apply_specdir(dir, root, parent, speconly);

	free_nodes(root);
}