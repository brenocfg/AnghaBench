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
typedef  struct addrinfo {int ai_addrlen; struct addrinfo const* ai_next; struct addrinfo const* ai_addr; int /*<<< orphan*/ * ai_canonname; } const addrinfo ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct addrinfo const*,struct addrinfo const*,int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clone_addrinfo(struct addrinfo *dest, struct addrinfo const *src)
{

	ATF_REQUIRE(dest != NULL);
	ATF_REQUIRE(src != NULL);

	memcpy(dest, src, sizeof(struct addrinfo));
	if (src->ai_canonname != NULL)
		dest->ai_canonname = strdup(src->ai_canonname);

	if (src->ai_addr != NULL) {
		dest->ai_addr = malloc(src->ai_addrlen);
		ATF_REQUIRE(dest->ai_addr != NULL);
		memcpy(dest->ai_addr, src->ai_addr, src->ai_addrlen);
	}

	if (src->ai_next != NULL) {
		dest->ai_next = malloc(sizeof(struct addrinfo));
		ATF_REQUIRE(dest->ai_next != NULL);
		clone_addrinfo(dest->ai_next, src->ai_next);
	}
}