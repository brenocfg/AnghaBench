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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_nvlist_flags (int /*<<< orphan*/  const*) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_exists_null (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_take_nvlist (int /*<<< orphan*/ *,char*) ; 

int
cap_limit_get(const cap_channel_t *chan, nvlist_t **limitsp)
{
	nvlist_t *nvlmsg;
	int error;

	nvlmsg = nvlist_create(channel_nvlist_flags(chan));
	nvlist_add_string(nvlmsg, "cmd", "limit_get");
	nvlmsg = cap_xfer_nvlist(chan, nvlmsg);
	if (nvlmsg == NULL)
		return (-1);
	error = (int)nvlist_get_number(nvlmsg, "error");
	if (error != 0) {
		nvlist_destroy(nvlmsg);
		errno = error;
		return (-1);
	}
	if (nvlist_exists_null(nvlmsg, "limits"))
		*limitsp = NULL;
	else
		*limitsp = nvlist_take_nvlist(nvlmsg, "limits");
	nvlist_destroy(nvlmsg);
	return (0);
}