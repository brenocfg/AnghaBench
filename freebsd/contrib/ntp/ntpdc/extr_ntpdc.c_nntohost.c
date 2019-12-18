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
 scalar_t__ SOCK_UNSPEC (int /*<<< orphan*/ *) ; 
 char const* refnumtoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  showhostnames ; 
 char const* socktohost (int /*<<< orphan*/ *) ; 
 char const* stoa (int /*<<< orphan*/ *) ; 

const char *
nntohost(
	sockaddr_u *netnum
	)
{
	if (!showhostnames || SOCK_UNSPEC(netnum))
		return stoa(netnum);
	else if (ISREFCLOCKADR(netnum))
		return refnumtoa(netnum);
	else
		return socktohost(netnum);
}