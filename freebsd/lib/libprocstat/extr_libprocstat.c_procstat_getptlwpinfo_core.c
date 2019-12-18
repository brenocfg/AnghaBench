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
struct ptrace_lwpinfo {int dummy; } ;
struct procstat_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_TYPE_PTLWPINFO ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 struct ptrace_lwpinfo* procstat_core_get (struct procstat_core*,int /*<<< orphan*/ ,void*,size_t*) ; 
 unsigned int procstat_core_note_count (struct procstat_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptrace_lwpinfo *
procstat_getptlwpinfo_core(struct procstat_core *core, unsigned int *cntp)
{
	void *buf;
	struct ptrace_lwpinfo *pl;
	unsigned int cnt;
	size_t len;

	cnt = procstat_core_note_count(core, PSC_TYPE_PTLWPINFO);
	if (cnt == 0)
		return (NULL);

	len = cnt * sizeof(*pl);
	buf = calloc(1, len);
	pl = procstat_core_get(core, PSC_TYPE_PTLWPINFO, buf, &len);
	if (pl == NULL) {
		free(buf);
		return (NULL);
	}
	*cntp = len / sizeof(*pl);
	return (pl);
}