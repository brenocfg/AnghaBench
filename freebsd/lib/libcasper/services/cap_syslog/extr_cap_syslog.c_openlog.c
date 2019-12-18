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
 int LOG_PERROR ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_descriptor (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 

void
cap_openlog(cap_channel_t *chan, const char *ident, int logopt, int facility)
{
	nvlist_t *nvl;

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "openlog");
	if (ident != NULL) {
		nvlist_add_string(nvl, "ident", ident);
	}
	nvlist_add_number(nvl, "logopt", logopt);
	nvlist_add_number(nvl, "facility", facility);
	if (logopt & LOG_PERROR) {
		nvlist_add_descriptor(nvl, "stderr", STDERR_FILENO);
	}
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL) {
		return;
	}
	nvlist_destroy(nvl);
}