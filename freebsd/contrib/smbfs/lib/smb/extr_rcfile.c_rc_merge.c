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
struct rcfile {int /*<<< orphan*/ * rf_f; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int rc_open (char const*,char*,struct rcfile**) ; 
 int /*<<< orphan*/  rc_parse (struct rcfile*) ; 

int
rc_merge(const char *filename, struct rcfile **rcfile)
{
	struct rcfile *rcp = *rcfile;
	FILE *f, *t;
	
	if (rcp == NULL) {
		return rc_open(filename, "r", rcfile);
	}
	f = fopen (filename, "r");
	if (f == NULL)
		return errno;
	t = rcp->rf_f;
	rcp->rf_f = f;
	rc_parse(rcp);
	rcp->rf_f = t;
	fclose(f);
	return 0;
}