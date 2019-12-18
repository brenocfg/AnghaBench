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
struct addrinfo {struct addrinfo* ai_addr; struct addrinfo* ai_canonname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct addrinfo*) ; 

void
freeaddrinfo(struct addrinfo *ai)
{
	if (ai->ai_canonname != NULL)
	{
		free(ai->ai_canonname);
		ai->ai_canonname = NULL;
	}
	if (ai->ai_addr != NULL)
	{
		free(ai->ai_addr);
		ai->ai_addr = NULL;
	}
	free(ai);
	ai = NULL;
}