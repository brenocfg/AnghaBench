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
struct netent_data {char* netbuf; char** net_aliases; int /*<<< orphan*/ * netf; } ;
struct netent {char* n_name; char** n_aliases; int /*<<< orphan*/  n_addrtype; int /*<<< orphan*/  n_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _MAXALIASES ; 
 int /*<<< orphan*/  _PATH_NETWORKS ; 
 int /*<<< orphan*/  __res_state () ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  inet_network (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static int
getnetent_p(struct netent *ne, struct netent_data *ned)
{
	char *p, *bp, *ep;
	char *cp, **q;
	int len;
	char line[BUFSIZ + 1];

	if (ned->netf == NULL &&
	    (ned->netf = fopen(_PATH_NETWORKS, "re")) == NULL)
		return (-1);
again:
	p = fgets(line, sizeof line, ned->netf);
	if (p == NULL)
		return (-1);
	if (*p == '#')
		goto again;
	cp = strpbrk(p, "#\n");
	if (cp != NULL)
		*cp = '\0';
	bp = ned->netbuf;
	ep = ned->netbuf + sizeof ned->netbuf;
	ne->n_name = bp;
	cp = strpbrk(p, " \t");
	if (cp == NULL)
		goto again;
	*cp++ = '\0';
	len = strlen(p) + 1;
	if (ep - bp < len) {
		RES_SET_H_ERRNO(__res_state(), NO_RECOVERY);
		return (-1);
	}
	strlcpy(bp, p, ep - bp);
	bp += len;
	while (*cp == ' ' || *cp == '\t')
		cp++;
	p = strpbrk(cp, " \t");
	if (p != NULL)
		*p++ = '\0';
	ne->n_net = inet_network(cp);
	ne->n_addrtype = AF_INET;
	q = ne->n_aliases = ned->net_aliases;
	if (p != NULL) {
		cp = p;
		while (cp && *cp) {
			if (*cp == ' ' || *cp == '\t') {
				cp++;
				continue;
			}
			if (q >= &ned->net_aliases[_MAXALIASES - 1])
				break;
			p = strpbrk(cp, " \t");
			if (p != NULL)
				*p++ = '\0';
			len = strlen(cp) + 1;
			if (ep - bp < len)
				break;
			strlcpy(bp, cp, ep - bp);
			*q++ = bp;
			bp += len;
			cp = p;
		}
	}
	*q = NULL;
	return (0);
}