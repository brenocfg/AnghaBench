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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

void
unsigned_relts_print(netdissect_options *ndo,
                     uint32_t secs)
{
	static const char *lengths[] = {"y", "w", "d", "h", "m", "s"};
	static const u_int seconds[] = {31536000, 604800, 86400, 3600, 60, 1};
	const char **l = lengths;
	const u_int *s = seconds;

	if (secs == 0) {
		ND_PRINT((ndo, "0s"));
		return;
	}
	while (secs > 0) {
		if (secs >= *s) {
			ND_PRINT((ndo, "%d%s", secs / *s, *l));
			secs -= (secs / *s) * *s;
		}
		s++;
		l++;
	}
}