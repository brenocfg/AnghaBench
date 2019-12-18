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

/* Variables and functions */
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (void*) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,int,char const*) ; 
 int /*<<< orphan*/  logprintf (char*,int) ; 

int
assertion_memory_filled_with(const char *file, int line,
    const void *_v1, const char *vd,
    size_t l, const char *ld,
    char b, const char *bd, void *extra)
{
	const char *v1 = (const char *)_v1;
	size_t c = 0;
	size_t i;
	(void)ld; /* UNUSED */

	assertion_count(file, line);

	for (i = 0; i < l; ++i) {
		if (v1[i] == b) {
			++c;
		}
	}
	if (c == l)
		return (1);

	failure_start(file, line, "%s (size %d) not filled with %s", vd, (int)l, bd);
	logprintf("   Only %d bytes were correct\n", (int)c);
	failure_finish(extra);
	return (0);
}