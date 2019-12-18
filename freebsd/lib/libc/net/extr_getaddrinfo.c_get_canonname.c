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
struct addrinfo {int ai_flags; int /*<<< orphan*/ * ai_canonname; } ;

/* Variables and functions */
 int AI_CANONNAME ; 
 int EAI_MEMORY ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int
get_canonname(const struct addrinfo *pai, struct addrinfo *ai, const char *str)
{
	if ((pai->ai_flags & AI_CANONNAME) != 0) {
		ai->ai_canonname = strdup(str);
		if (ai->ai_canonname == NULL)
			return EAI_MEMORY;
	}
	return 0;
}