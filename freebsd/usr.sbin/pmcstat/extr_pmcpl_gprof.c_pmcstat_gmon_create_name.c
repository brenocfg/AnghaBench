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
struct pmcstat_image {int /*<<< orphan*/  pi_samplename; } ;
typedef  int /*<<< orphan*/  pmcstat_interned_string ;
typedef  int /*<<< orphan*/  pmc_id_t ;
typedef  int /*<<< orphan*/  fullpath ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 char* pmcstat_pmcid_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcstat_string_intern (char*) ; 
 char* pmcstat_string_unintern (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char*) ; 

pmcstat_interned_string
pmcstat_gmon_create_name(const char *samplesdir, struct pmcstat_image *image,
    pmc_id_t pmcid)
{
	const char *pmcname;
	char fullpath[PATH_MAX];

	pmcname = pmcstat_pmcid_to_name(pmcid);
	if (!pmcname)
		err(EX_SOFTWARE, "ERROR: cannot find pmcid");

	(void) snprintf(fullpath, sizeof(fullpath),
	    "%s/%s/%s", samplesdir, pmcname,
	    pmcstat_string_unintern(image->pi_samplename));

	return (pmcstat_string_intern(fullpath));
}