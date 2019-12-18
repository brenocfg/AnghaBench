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
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int UC (char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 

char *
inet_ntoa(struct in_addr in)
{
	static char b[18];
	char *p;

	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
	(void)snprintf(b, sizeof(b),
	    "%u.%u.%u.%u", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
	return (b);
}