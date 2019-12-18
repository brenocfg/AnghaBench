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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int AF (int /*<<< orphan*/  const*) ; 
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int /*<<< orphan*/  PSOCK_ADDR4 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PSOCK_ADDR6 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SCOPE_VAR (int /*<<< orphan*/  const*) ; 
 int errno ; 
 int /*<<< orphan*/  inet_ntop (int const,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int socket_errno () ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

const char *
socktoa(
	const sockaddr_u *sock
	)
{
	int		saved_errno;
	char *		res;
	char *		addr;
	u_long		scope;

	saved_errno = socket_errno();
	LIB_GETBUF(res);

	if (NULL == sock) {
		strlcpy(res, "(null)", LIB_BUFLENGTH);
	} else {
		switch(AF(sock)) {

		case AF_INET:
		case AF_UNSPEC:
			inet_ntop(AF_INET, PSOCK_ADDR4(sock), res,
				  LIB_BUFLENGTH);
			break;

		case AF_INET6:
			inet_ntop(AF_INET6, PSOCK_ADDR6(sock), res,
				  LIB_BUFLENGTH);
			scope = SCOPE_VAR(sock);
			if (0 != scope && !strchr(res, '%')) {
				addr = res;
				LIB_GETBUF(res);
				snprintf(res, LIB_BUFLENGTH, "%s%%%lu",
					 addr, scope);
				res[LIB_BUFLENGTH - 1] = '\0';
			}
			break;

		default:
			snprintf(res, LIB_BUFLENGTH, 
				 "(socktoa unknown family %d)", 
				 AF(sock));
		}
	}
	errno = saved_errno;

	return res;
}