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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int CAP_SYSLOG_LIMIT ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void
cap_vsyslog(cap_channel_t *chan, int priority, const char *fmt, va_list ap)
{
	nvlist_t *nvl;
	char message[CAP_SYSLOG_LIMIT];

	(void)vsnprintf(message, sizeof(message), fmt, ap);

	nvl = nvlist_create(0);
	nvlist_add_string(nvl, "cmd", "vsyslog");
	nvlist_add_number(nvl, "priority", priority);
	nvlist_add_string(nvl, "message", message);
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL) {
		return;
	}
	nvlist_destroy(nvl);
}