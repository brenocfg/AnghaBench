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
struct sockaddr_in6 {int sin_len; int sin_family; int sin6_len; int sin6_family; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr_in {int sin_len; int sin_family; int sin6_len; int sin6_family; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct pf_addr {int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
typedef  int /*<<< orphan*/  sin6 ;
typedef  int /*<<< orphan*/  sin ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NOFQDN ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void
print_name(struct pf_addr *addr, sa_family_t af)
{
	char host[NI_MAXHOST];

	strlcpy(host, "?", sizeof(host));
	switch (af) {
	case AF_INET: {
		struct sockaddr_in sin;

		memset(&sin, 0, sizeof(sin));
		sin.sin_len = sizeof(sin);
		sin.sin_family = AF_INET;
		sin.sin_addr = addr->v4;
		getnameinfo((struct sockaddr *)&sin, sin.sin_len,
		    host, sizeof(host), NULL, 0, NI_NOFQDN);
		break;
	}
	case AF_INET6: {
		struct sockaddr_in6 sin6;

		memset(&sin6, 0, sizeof(sin6));
		sin6.sin6_len = sizeof(sin6);
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = addr->v6;
		getnameinfo((struct sockaddr *)&sin6, sin6.sin6_len,
		    host, sizeof(host), NULL, 0, NI_NOFQDN);
		break;
	}
	}
	printf("%s", host);
}