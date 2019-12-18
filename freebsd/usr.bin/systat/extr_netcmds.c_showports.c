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
struct servent {int /*<<< orphan*/  s_name; } ;
struct pitem {int /*<<< orphan*/  port; int /*<<< orphan*/  onoff; } ;

/* Variables and functions */
 int TCP ; 
 int UDP ; 
 int /*<<< orphan*/  addch (char) ; 
 struct servent* getservbyport (int /*<<< orphan*/ ,char*) ; 
 int nports ; 
 struct pitem* ports ; 
 int /*<<< orphan*/  printw (char*,int /*<<< orphan*/ ) ; 
 int protos ; 

__attribute__((used)) static void
showports(void)
{
	struct pitem *p;
	struct servent *sp;

	for (p = ports; p < ports+nports; p++) {
		sp = getservbyport(p->port,
		    protos == (TCP|UDP) ? 0 : protos == TCP ? "tcp" : "udp");
		if (!p->onoff)
			addch('!');
		if (sp)
			printw("%s ", sp->s_name);
		else
			printw("%d ", p->port);
	}
}