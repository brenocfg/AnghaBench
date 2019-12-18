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
struct servent {char* s_name; char* s_proto; char** s_aliases; int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  memset (struct servent*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static void
clone_servent(struct servent *dest, struct servent const *src)
{
	ATF_REQUIRE(dest != NULL);
	ATF_REQUIRE(src != NULL);

	char **cp;
	int aliases_num;

	memset(dest, 0, sizeof(struct servent));

	if (src->s_name != NULL) {
		dest->s_name = strdup(src->s_name);
		ATF_REQUIRE(dest->s_name != NULL);
	}

	if (src->s_proto != NULL) {
		dest->s_proto = strdup(src->s_proto);
		ATF_REQUIRE(dest->s_proto != NULL);
	}
	dest->s_port = src->s_port;

	if (src->s_aliases != NULL) {
		aliases_num = 0;
		for (cp = src->s_aliases; *cp; ++cp)
			++aliases_num;

		dest->s_aliases = calloc(aliases_num + 1, sizeof(char *));
		ATF_REQUIRE(dest->s_aliases != NULL);

		for (cp = src->s_aliases; *cp; ++cp) {
			dest->s_aliases[cp - src->s_aliases] = strdup(*cp);
			ATF_REQUIRE(dest->s_aliases[cp - src->s_aliases] != NULL);
		}
	}
}