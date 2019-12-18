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
struct procstat_core {int dummy; } ;
struct procstat {struct procstat_core* core; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCSTAT_CORE ; 
 struct procstat* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct procstat*) ; 
 struct procstat_core* procstat_core_open (char const*) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct procstat *
procstat_open_core(const char *filename)
{
	struct procstat *procstat;
	struct procstat_core *core;

	procstat = calloc(1, sizeof(*procstat));
	if (procstat == NULL) {
		warn("malloc()");
		return (NULL);
	}
	core = procstat_core_open(filename);
	if (core == NULL) {
		free(procstat);
		return (NULL);
	}
	procstat->type = PROCSTAT_CORE;
	procstat->core = core;
	return (procstat);
}