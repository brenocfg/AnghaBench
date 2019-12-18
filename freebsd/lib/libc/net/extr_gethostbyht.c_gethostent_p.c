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
struct hostent_data {char** h_addr_ptrs; char* hostbuf; char** host_aliases; scalar_t__ host_addr; int /*<<< orphan*/  hostf; } ;
struct hostent {char** h_addr_list; int h_length; int h_addrtype; char* h_name; char** h_aliases; } ;
typedef  int /*<<< orphan*/  res_state ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  HOST_NOT_FOUND ; 
 int IN6ADDRSZ ; 
 int INADDRSZ ; 
 int /*<<< orphan*/  NETDB_INTERNAL ; 
 int /*<<< orphan*/  NETDB_SUCCESS ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _MAXALIASES ; 
 int /*<<< orphan*/  _PATH_HOSTS ; 
 int /*<<< orphan*/  _map_v4v6_address (char*,char*) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ inet_pton (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 

__attribute__((used)) static int
gethostent_p(struct hostent *he, struct hostent_data *hed, int mapped,
    res_state statp)
{
	char *p, *bp, *ep;
	char *cp, **q;
	int af, len;
	char hostbuf[BUFSIZ + 1];

	if (!hed->hostf && !(hed->hostf = fopen(_PATH_HOSTS, "re"))) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (-1);
	}
 again:
	if (!(p = fgets(hostbuf, sizeof hostbuf, hed->hostf))) {
		RES_SET_H_ERRNO(statp, HOST_NOT_FOUND);
		return (-1);
	}
	if (*p == '#')
		goto again;
	cp = strpbrk(p, "#\n");
	if (cp != NULL)
		*cp = '\0';
	if (!(cp = strpbrk(p, " \t")))
		goto again;
	*cp++ = '\0';
	if (inet_pton(AF_INET6, p, hed->host_addr) > 0) {
		af = AF_INET6;
		len = IN6ADDRSZ;
	} else if (inet_pton(AF_INET, p, hed->host_addr) > 0) {
		if (mapped) {
			_map_v4v6_address((char *)hed->host_addr,
			    (char *)hed->host_addr);
			af = AF_INET6;
			len = IN6ADDRSZ;
		} else {
			af = AF_INET;
			len = INADDRSZ;
		}
	} else {
		goto again;
	}
	hed->h_addr_ptrs[0] = (char *)hed->host_addr;
	hed->h_addr_ptrs[1] = NULL;
	he->h_addr_list = hed->h_addr_ptrs;
	he->h_length = len;
	he->h_addrtype = af;
	while (*cp == ' ' || *cp == '\t')
		cp++;
	bp = hed->hostbuf;
	ep = hed->hostbuf + sizeof hed->hostbuf;
	he->h_name = bp;
	q = he->h_aliases = hed->host_aliases;
	if ((p = strpbrk(cp, " \t")) != NULL)
		*p++ = '\0';
	len = strlen(cp) + 1;
	if (ep - bp < len) {
		RES_SET_H_ERRNO(statp, NO_RECOVERY);
		return (-1);
	}
	strlcpy(bp, cp, ep - bp);
	bp += len;
	cp = p;
	while (cp && *cp) {
		if (*cp == ' ' || *cp == '\t') {
			cp++;
			continue;
		}
		if (q >= &hed->host_aliases[_MAXALIASES - 1])
			break;
		if ((p = strpbrk(cp, " \t")) != NULL)
			*p++ = '\0';
		len = strlen(cp) + 1;
		if (ep - bp < len)
			break;
		strlcpy(bp, cp, ep - bp);
		*q++ = bp;
		bp += len;
		cp = p;
	}
	*q = NULL;
	RES_SET_H_ERRNO(statp, NETDB_SUCCESS);
	return (0);
}