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
struct addrinfo {scalar_t__ ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;

/* Variables and functions */
 int EAI_MEMORY ; 
 struct addrinfo* copy_ai (struct addrinfo const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 

__attribute__((used)) static int
explore_copy(const struct addrinfo *pai, const struct addrinfo *src0,
    struct addrinfo **res)
{
	int error;
	struct addrinfo sentinel, *cur;
	const struct addrinfo *src;

	error = 0;
	sentinel.ai_next = NULL;
	cur = &sentinel;

	for (src = src0; src != NULL; src = src->ai_next) {
		if (src->ai_family != pai->ai_family)
			continue;

		cur->ai_next = copy_ai(src);
		if (!cur->ai_next) {
			error = EAI_MEMORY;
			goto fail;
		}

		cur->ai_next->ai_socktype = pai->ai_socktype;
		cur->ai_next->ai_protocol = pai->ai_protocol;
		cur = cur->ai_next;
	}

	*res = sentinel.ai_next;
	return 0;

fail:
	freeaddrinfo(sentinel.ai_next);
	return error;
}