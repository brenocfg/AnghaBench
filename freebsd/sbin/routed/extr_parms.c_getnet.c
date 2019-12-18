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
struct netent {scalar_t__ n_net; } ;
struct in_addr {int s_addr; } ;
typedef  int naddr ;
typedef  int /*<<< orphan*/  hname ;

/* Variables and functions */
 int HOST_MASK ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int RIP_DEFAULT ; 
 struct netent* getnetbyname (char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int inet_aton (char*,struct in_addr*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int ntohl (int) ; 
 int std_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 

int					/* 0=bad */
getnet(char *name,
       naddr *netp,			/* network in host byte order */
       naddr *maskp)			/* masks are always in host order */
{
	int i;
	struct netent *np;
	naddr mask;			/* in host byte order */
	struct in_addr in;		/* a network and so host byte order */
	char hname[MAXHOSTNAMELEN+1];
	char *mname, *p;


	/* Detect and separate "1.2.3.4/24"
	 */
	if (NULL != (mname = strrchr(name,'/'))) {
		i = (int)(mname - name);
		if (i > (int)sizeof(hname)-1)	/* name too long */
			return 0;
		memmove(hname, name, i);
		hname[i] = '\0';
		mname++;
		name = hname;
	}

	np = getnetbyname(name);
	if (np != NULL) {
		in.s_addr = (naddr)np->n_net;
		if (0 == (in.s_addr & 0xff000000))
			in.s_addr <<= 8;
		if (0 == (in.s_addr & 0xff000000))
			in.s_addr <<= 8;
		if (0 == (in.s_addr & 0xff000000))
			in.s_addr <<= 8;
	} else if (inet_aton(name, &in) == 1) {
		in.s_addr = ntohl(in.s_addr);
	} else if (!mname && !strcasecmp(name,"default")) {
		in.s_addr = RIP_DEFAULT;
	} else {
		return 0;
	}

	if (!mname) {
		/* we cannot use the interfaces here because we have not
		 * looked at them yet.
		 */
		mask = std_mask(htonl(in.s_addr));
		if ((~mask & in.s_addr) != 0)
			mask = HOST_MASK;
	} else {
		mask = (naddr)strtoul(mname, &p, 0);
		if (*p != '\0' || mask > 32)
			return 0;
		if (mask != 0)
			mask = HOST_MASK << (32-mask);
	}

	/* must have mask of 0 with default */
	if (mask != 0 && in.s_addr == RIP_DEFAULT)
		return 0;
	/* no host bits allowed in a network number */
	if ((~mask & in.s_addr) != 0)
		return 0;
	/* require non-zero network number */
	if ((mask & in.s_addr) == 0 && in.s_addr != RIP_DEFAULT)
		return 0;
	if (in.s_addr>>24 == 0 && in.s_addr != RIP_DEFAULT)
		return 0;
	if (in.s_addr>>24 == 0xff)
		return 0;

	*netp = in.s_addr;
	*maskp = mask;
	return 1;
}