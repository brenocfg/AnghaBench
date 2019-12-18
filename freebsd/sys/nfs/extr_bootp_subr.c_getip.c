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
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int getdec (char**) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 

__attribute__((used)) static int
getip(char **ptr, struct in_addr *addr)
{
	char *p;
	unsigned int ip;
	int val;

	p = *ptr;
	ip = 0;
	if (((val = getdec(&p)) < 0) || (val > 255))
		return 0;
	ip = val << 24;
	if (*p != '.')
		return 0;
	p++;
	if (((val = getdec(&p)) < 0) || (val > 255))
		return 0;
	ip |= (val << 16);
	if (*p != '.')
		return 0;
	p++;
	if (((val = getdec(&p)) < 0) || (val > 255))
		return 0;
	ip |= (val << 8);
	if (*p != '.')
		return 0;
	p++;
	if (((val = getdec(&p)) < 0) || (val > 255))
		return 0;
	ip |= val;

	addr->s_addr = htonl(ip);
	*ptr = p;
	return 1;
}