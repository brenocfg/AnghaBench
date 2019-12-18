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
struct node_host {scalar_t__ af; char* ifname; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

int
ifa_skip_if(const char *filter, struct node_host *p)
{
	int	n;

	if (p->af != AF_INET && p->af != AF_INET6)
		return (1);
	if (filter == NULL || !*filter)
		return (0);
	if (!strcmp(p->ifname, filter))
		return (0);	/* exact match */
	n = strlen(filter);
	if (n < 1 || n >= IFNAMSIZ)
		return (1);	/* sanity check */
	if (filter[n-1] >= '0' && filter[n-1] <= '9')
		return (1);	/* only do exact match in that case */
	if (strncmp(p->ifname, filter, n))
		return (1);	/* prefix doesn't match */
	return (p->ifname[n] < '0' || p->ifname[n] > '9');
}