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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct addrinfo* fetch_resolve (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 

int
fetch_bind(int sd, int af, const char *addr)
{
	struct addrinfo *cliai, *ai;
	int err;

	if ((cliai = fetch_resolve(addr, 0, af)) == NULL)
		return (-1);
	for (ai = cliai; ai != NULL; ai = ai->ai_next)
		if ((err = bind(sd, ai->ai_addr, ai->ai_addrlen)) == 0)
			break;
	if (err != 0)
		fetch_syserr();
	freeaddrinfo(cliai);
	return (err == 0 ? 0 : -1);
}