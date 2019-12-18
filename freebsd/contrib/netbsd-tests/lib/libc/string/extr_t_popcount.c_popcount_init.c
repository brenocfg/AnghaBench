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
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__* byte_count ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
popcount_init(const char *cfg_var)
{
	unsigned int i, j;

	if (strcasecmp(cfg_var, "YES")  == 0 ||
	    strcasecmp(cfg_var, "Y")    == 0 ||
	    strcasecmp(cfg_var, "1")    == 0 ||
	    strcasecmp(cfg_var, "T")    == 0 ||
	    strcasecmp(cfg_var, "TRUE") == 0) {
		for (i = 0; i < 256; ++i) {
			byte_count[i] = 0;
			for (j = i; j != 0; j >>= 1) {
				if (j & 1)
					++byte_count[i];
			}
		}
		return;
	}

	atf_tc_skip("config variable \"run_popcount\" not set to YES/TRUE");
}