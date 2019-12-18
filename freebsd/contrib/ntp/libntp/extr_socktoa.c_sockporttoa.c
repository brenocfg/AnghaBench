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
 scalar_t__ IS_IPV6 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int /*<<< orphan*/  SRCPORT (int /*<<< orphan*/  const*) ; 
 int errno ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int socket_errno () ; 
 char* socktoa (int /*<<< orphan*/  const*) ; 

const char *
sockporttoa(
	const sockaddr_u *sock
	)
{
	int		saved_errno;
	const char *	atext;
	char *		buf;

	saved_errno = socket_errno();
	atext = socktoa(sock);
	LIB_GETBUF(buf);
	snprintf(buf, LIB_BUFLENGTH,
		 (IS_IPV6(sock))
		     ? "[%s]:%hu"
		     : "%s:%hu",
		 atext, SRCPORT(sock));
	errno = saved_errno;

	return buf;
}