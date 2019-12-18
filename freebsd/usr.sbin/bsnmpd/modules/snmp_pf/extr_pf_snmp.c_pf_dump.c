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
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ altq_enabled ; 
 int /*<<< orphan*/  pfa_refresh () ; 
 scalar_t__ pfa_table_age ; 
 int /*<<< orphan*/  pfa_table_count ; 
 int /*<<< orphan*/  pfi_refresh () ; 
 scalar_t__ pfi_table_age ; 
 int /*<<< orphan*/  pfi_table_count ; 
 int /*<<< orphan*/  pfl_refresh () ; 
 scalar_t__ pfl_table_age ; 
 int /*<<< orphan*/  pfl_table_count ; 
 int /*<<< orphan*/  pfq_refresh () ; 
 scalar_t__ pfq_table_age ; 
 int /*<<< orphan*/  pfq_table_count ; 
 int /*<<< orphan*/  pft_refresh () ; 
 scalar_t__ pft_table_age ; 
 int /*<<< orphan*/  pft_table_count ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_dump(void)
{
	pfi_refresh();
	if (altq_enabled) {
		pfq_refresh();
	}
	pft_refresh();
	pfa_refresh();
	pfl_refresh();

	syslog(LOG_ERR, "Dump: pfi_table_age = %jd",
	    (intmax_t)pfi_table_age);
	syslog(LOG_ERR, "Dump: pfi_table_count = %d",
	    pfi_table_count);

	syslog(LOG_ERR, "Dump: pfq_table_age = %jd",
	    (intmax_t)pfq_table_age);
	syslog(LOG_ERR, "Dump: pfq_table_count = %d",
	    pfq_table_count);

	syslog(LOG_ERR, "Dump: pft_table_age = %jd",
	    (intmax_t)pft_table_age);
	syslog(LOG_ERR, "Dump: pft_table_count = %d",
	    pft_table_count);

	syslog(LOG_ERR, "Dump: pfa_table_age = %jd",
	    (intmax_t)pfa_table_age);
	syslog(LOG_ERR, "Dump: pfa_table_count = %d",
	    pfa_table_count);

	syslog(LOG_ERR, "Dump: pfl_table_age = %jd",
	    (intmax_t)pfl_table_age);
	syslog(LOG_ERR, "Dump: pfl_table_count = %d",
	    pfl_table_count);
}