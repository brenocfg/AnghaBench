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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t CHECKS_STR_SIZE ; 
 size_t LZMA_CHECK_ID_MAX ; 
 size_t UINT32_C (int) ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * check_names ; 
 int /*<<< orphan*/  my_snprintf (char**,size_t*,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_robot ; 

__attribute__((used)) static void
get_check_names(char buf[CHECKS_STR_SIZE],
		uint32_t checks, bool space_after_comma)
{
	// If we get called when there are no Checks to print, set checks
	// to 1 so that we print "None". This can happen in the robot mode
	// when printing the totals line if there are no valid input files.
	if (checks == 0)
		checks = 1;

	char *pos = buf;
	size_t left = CHECKS_STR_SIZE;

	const char *sep = space_after_comma ? ", " : ",";
	bool comma = false;

	for (size_t i = 0; i <= LZMA_CHECK_ID_MAX; ++i) {
		if (checks & (UINT32_C(1) << i)) {
			my_snprintf(&pos, &left, "%s%s",
					comma ? sep : "",
					opt_robot ? check_names[i]
						: _(check_names[i]));
			comma = true;
		}
	}

	return;
}