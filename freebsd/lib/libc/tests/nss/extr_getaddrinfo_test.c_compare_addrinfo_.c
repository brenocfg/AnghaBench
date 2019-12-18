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
struct addrinfo {scalar_t__ ai_flags; scalar_t__ ai_family; scalar_t__ ai_socktype; scalar_t__ ai_protocol; scalar_t__ ai_addrlen; struct addrinfo* ai_next; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/ * ai_canonname; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compare_addrinfo_(struct addrinfo *ai1, struct addrinfo *ai2)
{

	if ((ai1 == NULL) || (ai2 == NULL))
		return (-1);

	if (ai1->ai_flags != ai2->ai_flags ||
	    ai1->ai_family != ai2->ai_family ||
	    ai1->ai_socktype != ai2->ai_socktype ||
	    ai1->ai_protocol != ai2->ai_protocol ||
	    ai1->ai_addrlen != ai2->ai_addrlen ||
	    ((ai1->ai_addr == NULL || ai2->ai_addr == NULL) &&
	     ai1->ai_addr != ai2->ai_addr) ||
	    ((ai1->ai_canonname == NULL || ai2->ai_canonname == NULL) &&
	     ai1->ai_canonname != ai2->ai_canonname))
		return (-1);

	if (ai1->ai_canonname != NULL &&
	    strcmp(ai1->ai_canonname, ai2->ai_canonname) != 0)
		return (-1);

	if (ai1->ai_addr != NULL &&
	    memcmp(ai1->ai_addr, ai2->ai_addr, ai1->ai_addrlen) != 0)
		return (-1);

	if (ai1->ai_next == NULL && ai2->ai_next == NULL)
		return (0);
	else
		return (compare_addrinfo_(ai1->ai_next, ai2->ai_next));
}