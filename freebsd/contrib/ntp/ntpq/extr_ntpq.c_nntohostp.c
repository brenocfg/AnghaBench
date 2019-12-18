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
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 scalar_t__ ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 scalar_t__ SOCK_UNSPEC (int /*<<< orphan*/ *) ; 
 int SRCPORT (int /*<<< orphan*/ *) ; 
 char const* refnumtoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  showhostnames ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*,int) ; 
 char* socktohost (int /*<<< orphan*/ *) ; 
 char const* sptoa (int /*<<< orphan*/ *) ; 

const char *
nntohostp(
	sockaddr_u *netnum
	)
{
	const char *	hostn;
	char *		buf;

	if (!showhostnames || SOCK_UNSPEC(netnum))
		return sptoa(netnum);
	else if (ISREFCLOCKADR(netnum))
		return refnumtoa(netnum);

	hostn = socktohost(netnum);
	LIB_GETBUF(buf);
	snprintf(buf, LIB_BUFLENGTH, "%s:%u", hostn, SRCPORT(netnum));

	return buf;
}