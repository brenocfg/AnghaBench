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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  slog_closelog (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slog_openlog (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slog_setlogmask (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slog_vsyslog (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
syslog_command(const char *cmd, const nvlist_t *limits, nvlist_t *nvlin,
    nvlist_t *nvlout)
{

	if (strcmp(cmd, "vsyslog") == 0) {
		slog_vsyslog(limits, nvlin, nvlout);
	} else if (strcmp(cmd, "openlog") == 0) {
		slog_openlog(limits, nvlin, nvlout);
	} else if (strcmp(cmd, "closelog") == 0) {
		slog_closelog(limits, nvlin, nvlout);
	} else if (strcmp(cmd, "setlogmask") == 0) {
		slog_setlogmask(limits, nvlin, nvlout);
	} else {
		return (EINVAL);
	}

	return (0);
}