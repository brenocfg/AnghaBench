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
struct hostent {char* h_name; char** h_aliases; char** h_addr_list; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addrtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hostent*,int /*<<< orphan*/ ,int) ; 
 void* strdup (char*) ; 

__attribute__((used)) static void
clone_hostent(struct hostent *dest, struct hostent const *src)
{
	ATF_REQUIRE(dest != NULL);
	ATF_REQUIRE(src != NULL);

	char **cp;
	int aliases_num;
	int addrs_num;
	size_t offset;

	memset(dest, 0, sizeof(struct hostent));

	if (src->h_name != NULL) {
		dest->h_name = strdup(src->h_name);
		ATF_REQUIRE(dest->h_name != NULL);
	}

	dest->h_addrtype = src->h_addrtype;
	dest->h_length = src->h_length;

	if (src->h_aliases != NULL) {
		aliases_num = 0;
		for (cp = src->h_aliases; *cp; ++cp)
			++aliases_num;

		dest->h_aliases = calloc(aliases_num + 1, sizeof(char *));
		ATF_REQUIRE(dest->h_aliases != NULL);

		for (cp = src->h_aliases; *cp; ++cp) {
			dest->h_aliases[cp - src->h_aliases] = strdup(*cp);
			ATF_REQUIRE(dest->h_aliases[cp - src->h_aliases] != NULL);
		}
	}

	if (src->h_addr_list != NULL) {
		addrs_num = 0;
		for (cp = src->h_addr_list; *cp; ++cp)
			++addrs_num;

		dest->h_addr_list = calloc(addrs_num + 1, sizeof(char *));
		ATF_REQUIRE(dest->h_addr_list != NULL);

		for (cp = src->h_addr_list; *cp; ++cp) {
			offset = cp - src->h_addr_list;
			dest->h_addr_list[offset] = malloc(src->h_length);
			ATF_REQUIRE(dest->h_addr_list[offset] != NULL);
			memcpy(dest->h_addr_list[offset],
			    src->h_addr_list[offset], src->h_length);
		}
	}
}