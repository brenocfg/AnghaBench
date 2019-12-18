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
struct addrinfo {int ai_flags; int ai_family; int ai_socktype; int ai_protocol; struct addrinfo* ai_next; int /*<<< orphan*/ * ai_canonname; int /*<<< orphan*/ * ai_addr; scalar_t__ ai_addrlen; } ;
typedef  int /*<<< orphan*/  nvlname ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int NO_RECOVERY ; 
 int /*<<< orphan*/ * addrinfo_pack (struct addrinfo*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dns_allowed_family (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  dns_allowed_type (int /*<<< orphan*/  const*,char*) ; 
 char* dnvlist_get_string (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ nvlist_exists_number (int /*<<< orphan*/  const*,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int
dns_getaddrinfo(const nvlist_t *limits, const nvlist_t *nvlin, nvlist_t *nvlout)
{
	struct addrinfo hints, *hintsp, *res, *cur;
	const char *hostname, *servname;
	char nvlname[64];
	nvlist_t *elem;
	unsigned int ii;
	int error, family, n;

	if (!dns_allowed_type(limits, "NAME2ADDR") &&
	    !dns_allowed_type(limits, "NAME"))
		return (NO_RECOVERY);

	hostname = dnvlist_get_string(nvlin, "hostname", NULL);
	servname = dnvlist_get_string(nvlin, "servname", NULL);
	if (nvlist_exists_number(nvlin, "hints.ai_flags")) {
		hints.ai_flags = (int)nvlist_get_number(nvlin,
		    "hints.ai_flags");
		hints.ai_family = (int)nvlist_get_number(nvlin,
		    "hints.ai_family");
		hints.ai_socktype = (int)nvlist_get_number(nvlin,
		    "hints.ai_socktype");
		hints.ai_protocol = (int)nvlist_get_number(nvlin,
		    "hints.ai_protocol");
		hints.ai_addrlen = 0;
		hints.ai_addr = NULL;
		hints.ai_canonname = NULL;
		hints.ai_next = NULL;
		hintsp = &hints;
		family = hints.ai_family;
	} else {
		hintsp = NULL;
		family = AF_UNSPEC;
	}

	if (!dns_allowed_family(limits, family))
		return (NO_RECOVERY);

	error = getaddrinfo(hostname, servname, hintsp, &res);
	if (error != 0)
		goto out;

	for (cur = res, ii = 0; cur != NULL; cur = cur->ai_next, ii++) {
		elem = addrinfo_pack(cur);
		n = snprintf(nvlname, sizeof(nvlname), "res%u", ii);
		assert(n > 0 && n < (int)sizeof(nvlname));
		nvlist_move_nvlist(nvlout, nvlname, elem);
	}

	freeaddrinfo(res);
	error = 0;
out:
	return (error);
}