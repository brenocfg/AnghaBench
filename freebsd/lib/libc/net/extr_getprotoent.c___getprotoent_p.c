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
struct protoent_data {char** aliases; int /*<<< orphan*/ * fp; int /*<<< orphan*/  line; } ;
struct protoent {char* p_name; long p_proto; char** p_aliases; } ;

/* Variables and functions */
 long USHRT_MAX ; 
 int _MAXALIASES ; 
 int /*<<< orphan*/  _PATH_PROTOCOLS ; 
 char* fgets (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 char* strpbrk (char*,char*) ; 
 long strtol (char*,char**,int) ; 

int
__getprotoent_p(struct protoent *pe, struct protoent_data *ped)
{
	char *p;
	char *cp, **q, *endp;
	long l;

	if (ped->fp == NULL && (ped->fp = fopen(_PATH_PROTOCOLS, "re")) == NULL)
		return (-1);
again:
	if ((p = fgets(ped->line, sizeof ped->line, ped->fp)) == NULL)
		return (-1);
	if (*p == '#')
		goto again;
	cp = strpbrk(p, "#\n");
	if (cp != NULL)
		*cp = '\0';
	pe->p_name = p;
	cp = strpbrk(p, " \t");
	if (cp == NULL)
		goto again;
	*cp++ = '\0';
	while (*cp == ' ' || *cp == '\t')
		cp++;
	p = strpbrk(cp, " \t");
	if (p != NULL)
		*p++ = '\0';
	l = strtol(cp, &endp, 10);
	if (endp == cp || *endp != '\0' || l < 0 || l > USHRT_MAX)
		goto again;
	pe->p_proto = l;
	q = pe->p_aliases = ped->aliases;
	if (p != NULL) {
		cp = p;
		while (cp && *cp) {
			if (*cp == ' ' || *cp == '\t') {
				cp++;
				continue;
			}
			if (q < &ped->aliases[_MAXALIASES - 1])
				*q++ = cp;
			cp = strpbrk(cp, " \t");
			if (cp != NULL)
				*cp++ = '\0';
		}
	}
	*q = NULL;
	return (0);
}