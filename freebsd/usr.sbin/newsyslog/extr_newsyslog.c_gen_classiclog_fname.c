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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,...) ; 

__attribute__((used)) static void
gen_classiclog_fname(char *fname, size_t fname_sz, const char *archive_dir,
    const char *namepart, int numlogs_c)
{

	if (archive_dir[0] != '\0')
		(void) snprintf(fname, fname_sz, "%s/%s.%d", archive_dir,
		    namepart, numlogs_c);
	else
		(void) snprintf(fname, fname_sz, "%s.%d", namepart, numlogs_c);
}