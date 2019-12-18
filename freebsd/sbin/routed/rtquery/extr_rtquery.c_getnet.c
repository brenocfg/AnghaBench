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
typedef  int u_int ;
struct netinfo {void* n_mask; int /*<<< orphan*/  n_family; void* n_dst; } ;
struct netent {int n_net; } ;
struct in_addr {int s_addr; } ;
typedef  int /*<<< orphan*/  hname ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  RIP_AF_INET ; 
 struct netent* getnetbyname (char*) ; 
 void* htonl (int) ; 
 int inet_aton (char*,struct in_addr*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int ntohl (int) ; 
 int std_mask (int) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int				/* 0=bad */
getnet(char *name,
       struct netinfo *rt)
{
	int i;
	struct netent *nentp;
	u_int mask;
	struct in_addr in;
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

	nentp = getnetbyname(name);
	if (nentp != NULL) {
		in.s_addr = nentp->n_net;
	} else if (inet_aton(name, &in) == 1) {
		in.s_addr = ntohl(in.s_addr);
	} else {
		return 0;
	}

	if (mname == NULL) {
		mask = std_mask(in.s_addr);
		if ((~mask & in.s_addr) != 0)
			mask = 0xffffffff;
	} else {
		mask = (u_int)strtoul(mname, &p, 0);
		if (*p != '\0' || mask > 32)
			return 0;
		mask = 0xffffffff << (32-mask);
	}

	rt->n_dst = htonl(in.s_addr);
	rt->n_family = RIP_AF_INET;
	rt->n_mask = htonl(mask);
	return 1;
}