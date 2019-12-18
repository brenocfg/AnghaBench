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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  naddr ;

/* Variables and functions */
 struct hostent* gethostbyname (char*) ; 
 int inet_aton (char*,struct in_addr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int					/* 0=bad */
gethost(char *name,
	naddr *addrp)
{
	struct hostent *hp;
	struct in_addr in;


	/* Try for a number first, even in IRIX where gethostbyname()
	 * is smart.  This avoids hitting the name server which
	 * might be sick because routing is.
	 */
	if (inet_aton(name, &in) == 1) {
		/* get a good number, but check that it it makes some
		 * sense.
		 */
		if (ntohl(in.s_addr)>>24 == 0
		    || ntohl(in.s_addr)>>24 == 0xff)
			return 0;
		*addrp = in.s_addr;
		return 1;
	}

	hp = gethostbyname(name);
	if (hp) {
		memcpy(addrp, hp->h_addr, sizeof(*addrp));
		return 1;
	}

	return 0;
}