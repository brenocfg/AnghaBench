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
struct addrinfo {int /*<<< orphan*/  ai_canonname; struct addrinfo* ai_next; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
check_addrinfo_for_name(struct addrinfo *ai, char const *name)
{
	struct addrinfo *ai2;

	for (ai2 = ai; ai2 != NULL; ai2 = ai2->ai_next) {
		if (strcmp(ai2->ai_canonname, name) == 0)
			return (0);
	}

	return (-1);
}