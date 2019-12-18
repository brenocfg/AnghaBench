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
struct res_target {int dummy; } ;
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  nbuf ;
struct TYPE_5__ {int options; } ;

/* Variables and functions */
 int MAXDNAME ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 int RES_DEBUG ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int res_queryN (char const*,struct res_target*,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
res_querydomainN(const char *name, const char *domain,
    struct res_target *target, res_state res)
{
	char nbuf[MAXDNAME];
	const char *longname = nbuf;
	size_t n, d;

#ifdef DEBUG
	if (res->options & RES_DEBUG)
		printf(";; res_querydomain(%s, %s)\n",
			name, domain?domain:"<Nil>");
#endif
	if (domain == NULL) {
		/*
		 * Check for trailing '.';
		 * copy without '.' if present.
		 */
		n = strlen(name);
		if (n >= MAXDNAME) {
			RES_SET_H_ERRNO(res, NO_RECOVERY);
			return (-1);
		}
		if (n > 0 && name[--n] == '.') {
			strncpy(nbuf, name, n);
			nbuf[n] = '\0';
		} else
			longname = name;
	} else {
		n = strlen(name);
		d = strlen(domain);
		if (n + d + 1 >= MAXDNAME) {
			RES_SET_H_ERRNO(res, NO_RECOVERY);
			return (-1);
		}
		snprintf(nbuf, sizeof(nbuf), "%s.%s", name, domain);
	}
	return (res_queryN(longname, target, res));
}