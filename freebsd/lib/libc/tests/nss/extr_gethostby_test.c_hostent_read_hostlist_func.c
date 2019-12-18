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
struct hostent {int /*<<< orphan*/ * h_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __freehostent (struct hostent*) ; 
 struct hostent* __gethostbyname2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_type ; 
 int /*<<< orphan*/  clone_hostent (struct hostent*,struct hostent*) ; 
 int hostent_test_correctness (struct hostent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct hostent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static int
hostent_read_hostlist_func(struct hostent *he, char *line)
{
	struct hostent *result;
	int rv;

#ifdef DEBUG
	printf("resolving %s: ", line);
#endif
	result = __gethostbyname2(line, af_type);
	if (result != NULL) {
#ifdef DEBUG
		printf("found\n");
#endif

		rv = hostent_test_correctness(result, NULL);
		if (rv != 0) {
			__freehostent(result);
			return (rv);
		}

		clone_hostent(he, result);
		__freehostent(result);
	} else {
#ifdef DEBUG
		printf("not found\n");
#endif
 		memset(he, 0, sizeof(struct hostent));
		he->h_name = strdup(line);
		ATF_REQUIRE(he->h_name != NULL);
	}
	return (0);
}