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
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nfshost ; 
 struct addrinfo* nfshost_ai ; 
 scalar_t__ sacmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
namematch(struct addrinfo *ai)
{
	struct addrinfo *aip;

	if (nfshost == NULL || nfshost_ai == NULL)
		return (1);

	while (ai != NULL) {
		aip = nfshost_ai;
		while (aip != NULL) {
			if (sacmp(ai->ai_addr, aip->ai_addr) == 0)
				return (1);
			aip = aip->ai_next;
		}
		ai = ai->ai_next;
	}

	return (0);
}