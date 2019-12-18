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
struct hostent {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int errno ; 
 struct hostent* gethostbyaddr (void const*,int /*<<< orphan*/ ,int) ; 
 struct hostent* getipnodebyaddr (void const*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ use_ipnode_functions ; 

__attribute__((used)) static struct hostent *
__gethostbyaddr(const void *addr, socklen_t len, int af)
{
	struct hostent *he;
	int error;

	if (use_ipnode_functions) {
		error = 0;
		he = getipnodebyaddr(addr, len, af, &error);
		if (he == NULL)
			errno = error;
	} else
		he = gethostbyaddr(addr, len, af);

	return (he);
}