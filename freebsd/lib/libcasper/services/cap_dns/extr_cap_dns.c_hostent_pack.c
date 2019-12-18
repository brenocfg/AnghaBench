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
typedef  int /*<<< orphan*/  uint64_t ;
struct hostent {scalar_t__ h_length; int /*<<< orphan*/ ** h_addr_list; int /*<<< orphan*/ ** h_aliases; scalar_t__ h_addrtype; int /*<<< orphan*/ * h_name; } ;
typedef  int /*<<< orphan*/  nvlname ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void
hostent_pack(const struct hostent *hp, nvlist_t *nvl)
{
	unsigned int ii;
	char nvlname[64];
	int n;

	nvlist_add_string(nvl, "name", hp->h_name);
	nvlist_add_number(nvl, "addrtype", (uint64_t)hp->h_addrtype);
	nvlist_add_number(nvl, "length", (uint64_t)hp->h_length);

	if (hp->h_aliases == NULL) {
		nvlist_add_number(nvl, "naliases", 0);
	} else {
		for (ii = 0; hp->h_aliases[ii] != NULL; ii++) {
			n = snprintf(nvlname, sizeof(nvlname), "alias%u", ii);
			assert(n > 0 && n < (int)sizeof(nvlname));
			nvlist_add_string(nvl, nvlname, hp->h_aliases[ii]);
		}
		nvlist_add_number(nvl, "naliases", (uint64_t)ii);
	}

	if (hp->h_addr_list == NULL) {
		nvlist_add_number(nvl, "naddrs", 0);
	} else {
		for (ii = 0; hp->h_addr_list[ii] != NULL; ii++) {
			n = snprintf(nvlname, sizeof(nvlname), "addr%u", ii);
			assert(n > 0 && n < (int)sizeof(nvlname));
			nvlist_add_binary(nvl, nvlname, hp->h_addr_list[ii],
			    (size_t)hp->h_length);
		}
		nvlist_add_number(nvl, "naddrs", (uint64_t)ii);
	}
}