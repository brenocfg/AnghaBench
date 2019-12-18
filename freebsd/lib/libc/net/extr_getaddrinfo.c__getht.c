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
struct addrinfo {struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct addrinfo* _gethtent (int /*<<< orphan*/ **,char const*,struct addrinfo const*) ; 

__attribute__((used)) static struct addrinfo *
_getht(FILE **hostf, const char *name, const struct addrinfo *pai,
     struct addrinfo *cur)
{
	struct addrinfo *p;

	while ((p = _gethtent(hostf, name, pai)) != NULL) {
		cur->ai_next = p;
		while (cur && cur->ai_next)
			cur = cur->ai_next;
	}
	return (cur);
}