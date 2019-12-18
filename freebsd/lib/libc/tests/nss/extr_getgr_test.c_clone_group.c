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
struct group {char* gr_name; char* gr_passwd; char** gr_mem; int /*<<< orphan*/  gr_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  memset (struct group*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static void
clone_group(struct group *dest, struct group const *src)
{
	ATF_REQUIRE(dest != NULL);
	ATF_REQUIRE(src != NULL);

	char **cp;
	int members_num;

	memset(dest, 0, sizeof(struct group));

	if (src->gr_name != NULL) {
		dest->gr_name = strdup(src->gr_name);
		ATF_REQUIRE(dest->gr_name != NULL);
	}

	if (src->gr_passwd != NULL) {
		dest->gr_passwd = strdup(src->gr_passwd);
		ATF_REQUIRE(dest->gr_passwd != NULL);
	}
	dest->gr_gid = src->gr_gid;

	if (src->gr_mem != NULL) {
		members_num = 0;
		for (cp = src->gr_mem; *cp; ++cp)
			++members_num;

		dest->gr_mem = calloc(members_num + 1, sizeof(char *));
		ATF_REQUIRE(dest->gr_mem != NULL);

		for (cp = src->gr_mem; *cp; ++cp) {
			dest->gr_mem[cp - src->gr_mem] = strdup(*cp);
			ATF_REQUIRE(dest->gr_mem[cp - src->gr_mem] != NULL);
		}
	}
}