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
struct addrinfo {struct addrinfo* ai_next; scalar_t__ ai_protocol; scalar_t__ ai_socktype; scalar_t__ ai_family; scalar_t__ ai_flags; } ;
typedef  int /*<<< orphan*/  nvlname ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int EAI_MEMORY ; 
 struct addrinfo* addrinfo_unpack (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists_nvlist (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/ *,char*) ; 
 int snprintf (char*,int,char*,unsigned int) ; 

int
cap_getaddrinfo(cap_channel_t *chan, const char *hostname, const char *servname,
    const struct addrinfo *hints, struct addrinfo **res)
{
	struct addrinfo *firstai, *prevai, *curai;
	unsigned int ii;
	const nvlist_t *nvlai;
	char nvlname[64];
	nvlist_t *nvl;
	int error, n;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "getaddrinfo");
	if (hostname != NULL)
		nvlist_add_string(nvl, "hostname", hostname);
	if (servname != NULL)
		nvlist_add_string(nvl, "servname", servname);
	if (hints != NULL) {
		nvlist_add_number(nvl, "hints.ai_flags",
		    (uint64_t)hints->ai_flags);
		nvlist_add_number(nvl, "hints.ai_family",
		    (uint64_t)hints->ai_family);
		nvlist_add_number(nvl, "hints.ai_socktype",
		    (uint64_t)hints->ai_socktype);
		nvlist_add_number(nvl, "hints.ai_protocol",
		    (uint64_t)hints->ai_protocol);
	}
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL)
		return (EAI_MEMORY);
	if (nvlist_get_number(nvl, "error") != 0) {
		error = (int)nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		return (error);
	}

	nvlai = NULL;
	firstai = prevai = curai = NULL;
	for (ii = 0; ; ii++) {
		n = snprintf(nvlname, sizeof(nvlname), "res%u", ii);
		assert(n > 0 && n < (int)sizeof(nvlname));
		if (!nvlist_exists_nvlist(nvl, nvlname))
			break;
		nvlai = nvlist_get_nvlist(nvl, nvlname);
		curai = addrinfo_unpack(nvlai);
		if (curai == NULL)
			break;
		if (prevai != NULL)
			prevai->ai_next = curai;
		else if (firstai == NULL)
			firstai = curai;
		prevai = curai;
	}
	nvlist_destroy(nvl);
	if (curai == NULL && nvlai != NULL) {
		if (firstai == NULL)
			freeaddrinfo(firstai);
		return (EAI_MEMORY);
	}

	*res = firstai;
	return (0);
}