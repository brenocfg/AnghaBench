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
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_1__* res_state ;
struct TYPE_5__ {int options; } ;

/* Variables and functions */
 int MAXDNAME ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 int RES_DEBUG ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,int,int) ; 
 int res_nquery (TYPE_1__*,char const*,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int
res_nquerydomain(res_state statp,
	    const char *name,
	    const char *domain,
	    int class, int type,	/*%< class and type of query */
	    u_char *answer,		/*%< buffer to put answer */
	    int anslen)		/*%< size of answer */
{
	char nbuf[MAXDNAME];
	const char *longname = nbuf;
	int n, d;

#ifdef DEBUG
	if (statp->options & RES_DEBUG)
		printf(";; res_nquerydomain(%s, %s, %d, %d)\n",
		       name, domain?domain:"<Nil>", class, type);
#endif
	if (domain == NULL) {
		/*
		 * Check for trailing '.';
		 * copy without '.' if present.
		 */
		n = strlen(name);
		if (n >= MAXDNAME) {
			RES_SET_H_ERRNO(statp, NO_RECOVERY);
			return (-1);
		}
		n--;
		if (n >= 0 && name[n] == '.') {
			strncpy(nbuf, name, n);
			nbuf[n] = '\0';
		} else
			longname = name;
	} else {
		n = strlen(name);
		d = strlen(domain);
		if (n + d + 1 >= MAXDNAME) {
			RES_SET_H_ERRNO(statp, NO_RECOVERY);
			return (-1);
		}
		sprintf(nbuf, "%s.%s", name, domain);
	}
	return (res_nquery(statp, longname, class, type, answer, anslen));
}