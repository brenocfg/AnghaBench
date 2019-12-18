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
typedef  int u_char ;
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
plen2mask(struct sockaddr_in6 *mask, int plen)
{
	u_char *cp = (unsigned char *)&mask->sin6_addr;

	memset(mask, 0, sizeof(*mask));
	mask->sin6_family = AF_INET6; /* just in case */
	mask->sin6_len = sizeof(*mask);

	for(; plen >= 8; plen -= 8)
		*cp++ = 0xff;
	if (plen > 0)
		*cp = (0xff << (8 - plen));
}