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
struct procstat {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCSTAT_SYSCTL ; 
 struct procstat* calloc (int,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct procstat *
procstat_open_sysctl(void)
{
	struct procstat *procstat;

	procstat = calloc(1, sizeof(*procstat));
	if (procstat == NULL) {
		warn("malloc()");
		return (NULL);
	}
	procstat->type = PROCSTAT_SYSCTL;
	return (procstat);
}