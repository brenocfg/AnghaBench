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
struct hostent {char** h_addr_list; int /*<<< orphan*/  h_addrtype; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_name; } ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int check_addrinfo_for_addr (struct addrinfo*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_addrinfo_for_name (struct addrinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
is_hostent_equal(struct hostent *he, struct addrinfo *ai)
{
	char **cp;
	int rv;

#ifdef DEBUG
	printf("checking equality of he and ai\n");
#endif

	rv = check_addrinfo_for_name(ai, he->h_name);
	if (rv != 0) {
		printf("not equal - he->h_name couldn't be found\n");
		return (rv);
	}

	for (cp = he->h_addr_list; *cp; ++cp) {
		rv = check_addrinfo_for_addr(ai, *cp, he->h_length,
			he->h_addrtype);
		if (rv != 0) {
			printf("not equal - one of he->h_addr_list couldn't be found\n");
			return (rv);
		}
	}

#ifdef DEBUG
	printf("equal\n");
#endif

	return (0);
}