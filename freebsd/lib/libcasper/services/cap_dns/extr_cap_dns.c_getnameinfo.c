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
struct sockaddr {int dummy; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int EAI_MEMORY ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,struct sockaddr const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_exists_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

int
cap_getnameinfo(cap_channel_t *chan, const struct sockaddr *sa, socklen_t salen,
    char *host, size_t hostlen, char *serv, size_t servlen, int flags)
{
	nvlist_t *nvl;
	int error;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "getnameinfo");
	nvlist_add_number(nvl, "hostlen", (uint64_t)hostlen);
	nvlist_add_number(nvl, "servlen", (uint64_t)servlen);
	nvlist_add_binary(nvl, "sa", sa, (size_t)salen);
	nvlist_add_number(nvl, "flags", (uint64_t)flags);
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL)
		return (EAI_MEMORY);
	if (nvlist_get_number(nvl, "error") != 0) {
		error = (int)nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		return (error);
	}

	if (host != NULL && nvlist_exists_string(nvl, "host"))
		strlcpy(host, nvlist_get_string(nvl, "host"), hostlen + 1);
	if (serv != NULL && nvlist_exists_string(nvl, "serv"))
		strlcpy(serv, nvlist_get_string(nvl, "serv"), servlen + 1);
	nvlist_destroy(nvl);
	return (0);
}