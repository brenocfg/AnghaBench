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
struct hostent {int dummy; } ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int NO_RECOVERY ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int h_errno ; 
 int /*<<< orphan*/  hent ; 
 struct hostent* hostent_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 

struct hostent *
cap_gethostbyaddr(cap_channel_t *chan, const void *addr, socklen_t len,
    int type)
{
	struct hostent *hp;
	nvlist_t *nvl;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "gethostbyaddr");
	nvlist_add_binary(nvl, "addr", addr, (size_t)len);
	nvlist_add_number(nvl, "family", (uint64_t)type);
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL) {
		h_errno = NO_RECOVERY;
		return (NULL);
	}
	if (nvlist_get_number(nvl, "error") != 0) {
		h_errno = (int)nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		return (NULL);
	}
	hp = hostent_unpack(nvl, &hent);
	nvlist_destroy(nvl);
	return (hp);
}