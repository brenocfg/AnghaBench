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
struct hostent {char* h_name; int h_addrtype; char** h_addr_list; int /*<<< orphan*/  h_length; int /*<<< orphan*/ * h_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRLEN (int) ; 
 struct hostent* _hpcopy (struct hostent*,int*) ; 

__attribute__((used)) static struct hostent *
_hpaddr(int af, const char *name, void *addr, int *errp)
{
	struct hostent *hp, hpbuf;
	char *addrs[2];

	hp = &hpbuf;
	hp->h_name = (char *)name;
	hp->h_aliases = NULL;
	hp->h_addrtype = af;
	hp->h_length = ADDRLEN(af);
	hp->h_addr_list = addrs;
	addrs[0] = (char *)addr;
	addrs[1] = NULL;
	return (_hpcopy(hp, errp));
}