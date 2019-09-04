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
struct func {int dummy; } ;
struct file {char* name; struct file* link; scalar_t__ funcs; scalar_t__ counts; scalar_t__ count; scalar_t__ size; } ;

/* Variables and functions */
 int NELEMS (char**) ; 
 int /*<<< orphan*/  NEW (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 int /*<<< orphan*/  acaller (char*,char*,int,int,int,struct func*) ; 
 struct func* afunction (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  apoint (int,char*,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct file* filelist ; 
 int /*<<< orphan*/  findfile (char*) ; 
 int getd () ; 
 char* getstr () ; 

__attribute__((used)) static int gather(void) {
	int i, nfiles, nfuncs, npoints;
	char *files[64];

	if ((nfiles = getd()) < 0)
		return 0;
	assert(nfiles < NELEMS(files));
	for (i = 0; i < nfiles; i++) {
		if ((files[i] = getstr()) == 0)
			return -1;
		if (!findfile(files[i])) {
			struct file *new;
			NEW(new, PERM);
			new->name = files[i];
			new->size = new->count = 0;
			new->counts = 0;
			new->funcs = 0;
			new->link = filelist;
			filelist = new;
		}
	}
	if ((nfuncs = getd()) < 0)
		return -1;
	for (i = 0; i < nfuncs; i++) {
		struct func *q;
		char *name, *file;
		int f, x, y, count;
		if ((name = getstr()) == 0 || (f = getd()) <= 0
		|| (x = getd()) < 0 || (y = getd()) < 0 || (count = getd()) < 0)
			return -1;
		q = afunction(name, files[f-1], x, y, count);
		if ((name = getstr()) == 0 || (file = getstr()) == 0
		|| (x = getd()) < 0 || (y = getd()) < 0)
			return -1;
		if (*name != '?')
			acaller(name, file, x, y, count, q);
	}
	if ((npoints = getd()) < 0)
		return -1;
	for (i = 0; i < npoints; i++) {
		int f, x, y, count;
		if ((f = getd()) < 0 || (x = getd()) < 0 || (y = getd()) < 0
		|| (count = getd()) < 0)
			return -1;
		if (f)
			apoint(i, files[f-1], x, y, count);
	}
	return 1;
}