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
struct in_addr {int dummy; } ;
struct iaddr {scalar_t__ len; int /*<<< orphan*/  iabuf; } ;
typedef  int /*<<< orphan*/  pbuf ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

char *
piaddr(struct iaddr addr)
{
	static char pbuf[32];
	struct in_addr a;
	char *s;

	memcpy(&a, &(addr.iabuf), sizeof(struct in_addr));

	if (addr.len == 0)
		strlcpy(pbuf, "<null address>", sizeof(pbuf));
	else {
		s = inet_ntoa(a);
		if (s != NULL)
			strlcpy(pbuf, s, sizeof(pbuf));
		else
			strlcpy(pbuf, "<invalid address>", sizeof(pbuf));
	}
	return (pbuf);
}