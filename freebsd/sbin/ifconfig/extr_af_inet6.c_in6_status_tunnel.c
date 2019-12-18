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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct in6_ifreq {int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifr_addr; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  in6_ifr ;
typedef  int /*<<< orphan*/  dst ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  SIOCGIFPDSTADDR_IN6 ; 
 int /*<<< orphan*/  SIOCGIFPSRCADDR_IN6 ; 
 scalar_t__ getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct in6_ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
in6_status_tunnel(int s)
{
	char src[NI_MAXHOST];
	char dst[NI_MAXHOST];
	struct in6_ifreq in6_ifr;
	const struct sockaddr *sa = (const struct sockaddr *) &in6_ifr.ifr_addr;

	memset(&in6_ifr, 0, sizeof(in6_ifr));
	strlcpy(in6_ifr.ifr_name, name, sizeof(in6_ifr.ifr_name));

	if (ioctl(s, SIOCGIFPSRCADDR_IN6, (caddr_t)&in6_ifr) < 0)
		return;
	if (sa->sa_family != AF_INET6)
		return;
	if (getnameinfo(sa, sa->sa_len, src, sizeof(src), 0, 0,
	    NI_NUMERICHOST) != 0)
		src[0] = '\0';

	if (ioctl(s, SIOCGIFPDSTADDR_IN6, (caddr_t)&in6_ifr) < 0)
		return;
	if (sa->sa_family != AF_INET6)
		return;
	if (getnameinfo(sa, sa->sa_len, dst, sizeof(dst), 0, 0,
	    NI_NUMERICHOST) != 0)
		dst[0] = '\0';

	printf("\ttunnel inet6 %s --> %s\n", src, dst);
}