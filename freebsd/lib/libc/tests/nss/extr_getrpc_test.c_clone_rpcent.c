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
struct rpcent {char* r_name; char** r_aliases; int /*<<< orphan*/  r_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  memset (struct rpcent*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static void
clone_rpcent(struct rpcent *dest, struct rpcent const *src)
{
	ATF_REQUIRE(dest != NULL);
	ATF_REQUIRE(src != NULL);

	char **cp;
	int aliases_num;

	memset(dest, 0, sizeof(struct rpcent));

	if (src->r_name != NULL) {
		dest->r_name = strdup(src->r_name);
		ATF_REQUIRE(dest->r_name != NULL);
	}

	dest->r_number = src->r_number;

	if (src->r_aliases != NULL) {
		aliases_num = 0;
		for (cp = src->r_aliases; *cp; ++cp)
			++aliases_num;

		dest->r_aliases = calloc(aliases_num + 1, sizeof(char *));
		ATF_REQUIRE(dest->r_aliases != NULL);

		for (cp = src->r_aliases; *cp; ++cp) {
			dest->r_aliases[cp - src->r_aliases] = strdup(*cp);
			ATF_REQUIRE(dest->r_aliases[cp - src->r_aliases] != NULL);
		}
	}
}