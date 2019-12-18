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
struct hostent {char* h_name; } ;
struct hitem {int /*<<< orphan*/  addr; int /*<<< orphan*/  onoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  addch (char) ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 struct hitem* hosts ; 
 scalar_t__ inet_ntoa (int /*<<< orphan*/ ) ; 
 int nhosts ; 
 int /*<<< orphan*/  printw (char*,char*) ; 

__attribute__((used)) static void
showhosts(void)
{
	struct hitem *p;
	struct hostent *hp;

	for (p = hosts; p < hosts+nhosts; p++) {
		hp = gethostbyaddr((char *)&p->addr, sizeof (p->addr), AF_INET);
		if (!p->onoff)
			addch('!');
		printw("%s ", hp ? hp->h_name : (char *)inet_ntoa(p->addr));
	}
}