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
struct xaddr {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int addr_sa_to_xaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xaddr*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,char,int) ; 

__attribute__((used)) static int
addr_pton(const char *p, struct xaddr *n)
{
	struct addrinfo hints, *ai = NULL;
	int ret = -1;

	memset(&hints, '\0', sizeof(hints));
	hints.ai_flags = AI_NUMERICHOST;

	if (p == NULL || getaddrinfo(p, NULL, &hints, &ai) != 0)
		goto out;
	if (ai == NULL || ai->ai_addr == NULL)
		goto out;
	if (n != NULL && addr_sa_to_xaddr(ai->ai_addr, ai->ai_addrlen, n) == -1)
		goto out;
	/* success */
	ret = 0;
 out:
	if (ai != NULL)
		freeaddrinfo(ai);
	return ret;
}