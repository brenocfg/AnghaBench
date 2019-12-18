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
struct pitem {scalar_t__ port; int onoff; } ;
struct in_conninfo {scalar_t__ inc_lport; scalar_t__ inc_fport; } ;

/* Variables and functions */
 int nports ; 
 struct pitem* ports ; 

int
checkport(struct in_conninfo *inc)
{
	struct pitem *p;

	if (ports)
	for (p = ports; p < ports+nports; p++)
		if (p->port == inc->inc_lport || p->port == inc->inc_fport)
			return (p->onoff);
	return (1);
}