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
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int addrinfo_test_correctness (struct addrinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clone_addrinfo (struct addrinfo*,struct addrinfo*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  hints ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
addrinfo_read_hostlist_func(struct addrinfo *ai, char *line)
{
	struct addrinfo *result;
	int rv;

	printf("resolving %s: ", line);
	rv = getaddrinfo(line, NULL, &hints, &result);
	if (rv == 0) {
		printf("found\n");

		rv = addrinfo_test_correctness(result, NULL);
		if (rv != 0) {
			freeaddrinfo(result);
			result = NULL;
			return (rv);
		}

		clone_addrinfo(ai, result);
		freeaddrinfo(result);
		result = NULL;
	} else {
		printf("not found\n");

 		memset(ai, 0, sizeof(struct addrinfo));
	}
	return (0);
}