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
 int /*<<< orphan*/  PSC_TYPE_UMASK ; 
 int /*<<< orphan*/  free (unsigned short*) ; 
 unsigned short* procstat_core_get (struct procstat_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
procstat_getumask_core(struct procstat_core *core, unsigned short *maskp)
{
	size_t len;
	unsigned short *buf;

	buf = procstat_core_get(core, PSC_TYPE_UMASK, NULL, &len);
	if (buf == NULL)
		return (-1);
	if (len < sizeof(*maskp)) {
		free(buf);
		return (-1);
	}
	*maskp = *buf;
	free(buf);
	return (0);
}