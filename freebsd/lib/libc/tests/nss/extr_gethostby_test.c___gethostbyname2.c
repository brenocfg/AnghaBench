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

/* Variables and functions */
 int errno ; 
 struct hostent* gethostbyname2 (char const*,int) ; 
 struct hostent* getipnodebyname (char const*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ipnode_flags ; 
 scalar_t__ use_ipnode_functions ; 

__attribute__((used)) static struct hostent *
__gethostbyname2(const char *name, int af)
{
	struct hostent *he;
	int error;

	if (use_ipnode_functions) {
		error = 0;
		he = getipnodebyname(name, af, ipnode_flags, &error);
		if (he == NULL)
			errno = error;
	} else
		he = gethostbyname2(name, af);

	return (he);
}