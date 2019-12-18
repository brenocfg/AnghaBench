#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_4__ {scalar_t__ domain; char* name; } ;
struct TYPE_3__ {scalar_t__ type; char* name; } ;

/* Variables and functions */
 scalar_t__ PF_LOCAL ; 
 scalar_t__ PF_ROUTE ; 
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*) ; 
 scalar_t__ random () ; 
 int rt_numfibs ; 
 int /*<<< orphan*/  so_setfib (int,int,size_t,size_t) ; 
 int socket (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 TYPE_2__* t_dom ; 
 TYPE_1__* t_type ; 
 int testno ; 

__attribute__((used)) static void
t(u_int dom, u_int type)
{
	int i, s;

	/* PF_ROUTE only supports RAW socket types, while PF_LOCAL does not. */
	if (t_dom[dom].domain == PF_ROUTE && t_type[type].type != SOCK_RAW)
		return;
	if (t_dom[dom].domain == PF_LOCAL && t_type[type].type == SOCK_RAW)
		return;

	/* Open socket for given combination. */
	s = socket(t_dom[dom].domain, t_type[type].type, 0);
	if (s == -1) {
		printf("not ok %d %s_%s # socket(): %s\n", testno,
		    t_dom[dom].name, t_type[type].name, strerror(errno));
		testno++;
		return;
	}
	
	/* Test FIBs -2, -1, 0, .. n, n + 1, n + 2. */
	for (i = -2; i <= (rt_numfibs + 2); i++)
		so_setfib(s, i, dom, type);

	/* Test 3 random FIB numbers. */
	for (i = 0; i < 3; i++)
		so_setfib(s, (int)random(), dom, type);

	/* Close socket. */
	close(s);
}