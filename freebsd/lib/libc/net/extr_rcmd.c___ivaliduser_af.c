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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int sin_len; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int __ivaliduser_sa (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

int
__ivaliduser_af(FILE *hostf, const void *raddr, const char *luser,
    const char *ruser, int af, int len)
{
	struct sockaddr *sa = NULL;
	struct sockaddr_in *sin = NULL;
#ifdef INET6
	struct sockaddr_in6 *sin6 = NULL;
#endif
	struct sockaddr_storage ss;

	memset(&ss, 0, sizeof(ss));
	switch (af) {
	case AF_INET:
		if (len != sizeof(sin->sin_addr))
			return -1;
		sin = (struct sockaddr_in *)&ss;
		sin->sin_family = AF_INET;
		sin->sin_len = sizeof(struct sockaddr_in);
		memcpy(&sin->sin_addr, raddr, sizeof(sin->sin_addr));
		break;
#ifdef INET6
	case AF_INET6:
		if (len != sizeof(sin6->sin6_addr))
			return -1;
		/* you will lose scope info */
		sin6 = (struct sockaddr_in6 *)&ss;
		sin6->sin6_family = AF_INET6;
		sin6->sin6_len = sizeof(struct sockaddr_in6);
		memcpy(&sin6->sin6_addr, raddr, sizeof(sin6->sin6_addr));
		break;
#endif
	default:
		return -1;
	}

	sa = (struct sockaddr *)&ss;
	return __ivaliduser_sa(hostf, sa, sa->sa_len, luser, ruser);
}