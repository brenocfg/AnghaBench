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
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  hexdump (char const*,char const*,size_t,size_t) ; 
 int /*<<< orphan*/  logprintf (char*,...) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 

int
assertion_equal_mem(const char *file, int line,
    const void *_v1, const char *e1,
    const void *_v2, const char *e2,
    size_t l, const char *ld, void *extra)
{
	const char *v1 = (const char *)_v1;
	const char *v2 = (const char *)_v2;
	size_t offset;

	assertion_count(file, line);
	if (v1 == v2 || (v1 != NULL && v2 != NULL && memcmp(v1, v2, l) == 0))
		return (1);
	if (v1 == NULL || v2 == NULL)
		return (0);

	failure_start(file, line, "%s != %s", e1, e2);
	logprintf("      size %s = %d\n", ld, (int)l);
	/* Dump 48 bytes (3 lines) so that the first difference is
	 * in the second line. */
	offset = 0;
	while (l > 64 && memcmp(v1, v2, 32) == 0) {
		/* Two lines agree, so step forward one line. */
		v1 += 16;
		v2 += 16;
		l -= 16;
		offset += 16;
	}
	logprintf("      Dump of %s\n", e1);
	hexdump(v1, v2, l < 128 ? l : 128, offset);
	logprintf("      Dump of %s\n", e2);
	hexdump(v2, v1, l < 128 ? l : 128, offset);
	logprintf("\n");
	failure_finish(extra);
	return (0);
}