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
struct printer {char* spool_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  local_host ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
lmktemp(const struct printer *pp, const char *id, int num, int len)
{
	register char *s;

	if ((s = malloc(len)) == NULL)
		errx(1, "out of memory");
	(void) snprintf(s, len, "%s/%sA%03d%s", pp->spool_dir, id, num,
	    local_host);
	return(s);
}