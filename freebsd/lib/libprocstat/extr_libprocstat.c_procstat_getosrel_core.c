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

/* Variables and functions */
 int /*<<< orphan*/  PSC_TYPE_OSREL ; 
 int /*<<< orphan*/  free (int*) ; 
 int* procstat_core_get (struct procstat_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
procstat_getosrel_core(struct procstat_core *core, int *osrelp)
{
	size_t len;
	int *buf;

	buf = procstat_core_get(core, PSC_TYPE_OSREL, NULL, &len);
	if (buf == NULL)
		return (-1);
	if (len < sizeof(*osrelp)) {
		free(buf);
		return (-1);
	}
	*osrelp = *buf;
	free(buf);
	return (0);
}