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
struct rcfile {int /*<<< orphan*/ * rf_f; int /*<<< orphan*/  rf_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rcfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct rcfile*,int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 struct rcfile* malloc (int) ; 
 int /*<<< orphan*/  pf_head ; 
 struct rcfile* rc_cachelookup (char const*) ; 
 int /*<<< orphan*/  rc_parse (struct rcfile*) ; 
 int /*<<< orphan*/  rf_next ; 
 int /*<<< orphan*/  strdup (char const*) ; 

int
rc_open(const char *filename, const char *mode, struct rcfile **rcfile)
{
	struct rcfile *rcp;
	FILE *f;
	
	rcp = rc_cachelookup(filename);
	if (rcp) {
		*rcfile = rcp;
		return 0;
	}
	f = fopen(filename, mode);
	if (f == NULL)
		return errno;
	rcp = malloc(sizeof(struct rcfile));
	if (rcp == NULL) {
		fclose(f);
		return ENOMEM;
	}
	bzero(rcp, sizeof(struct rcfile));
	rcp->rf_name = strdup(filename);
	rcp->rf_f = f;
	SLIST_INSERT_HEAD(&pf_head, rcp, rf_next);
	rc_parse(rcp);
	*rcfile = rcp;
	return 0;
}