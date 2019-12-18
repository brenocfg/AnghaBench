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
typedef  int /*<<< orphan*/  u_int32 ;
struct hostent {int /*<<< orphan*/  h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int LOOPBACKHOST ; 
 int LOOPBACKNET ; 
 int LOOPBACKNETMASK ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 char* numtoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
numtohost(
	u_int32 netnum
	)
{
	char *bp;
	struct hostent *hp;

	/*
	 * This is really gross, but saves lots of hanging looking for
	 * hostnames for the radio clocks.  Don't bother looking up
	 * addresses on the loopback network except for the loopback
	 * host itself.
	 */
	if ((((ntohl(netnum) & LOOPBACKNETMASK) == LOOPBACKNET)
	     && (ntohl(netnum) != LOOPBACKHOST))
	    || ((hp = gethostbyaddr((char *)&netnum, sizeof netnum, AF_INET))
		== 0))
	    return numtoa(netnum);
	
	LIB_GETBUF(bp);
	strlcpy(bp, hp->h_name, LIB_BUFLENGTH);

	return bp;
}