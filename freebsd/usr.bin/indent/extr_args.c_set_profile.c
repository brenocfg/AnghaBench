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
typedef  int /*<<< orphan*/  fname ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (char*) ; 
 char* option_source ; 
 int /*<<< orphan*/  scan_profile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

void
set_profile(const char *profile_name)
{
    FILE *f;
    char fname[PATH_MAX];
    static char prof[] = ".indent.pro";

    if (profile_name == NULL)
	snprintf(fname, sizeof(fname), "%s/%s", getenv("HOME"), prof);
    else
	snprintf(fname, sizeof(fname), "%s", profile_name + 2);
    if ((f = fopen(option_source = fname, "r")) != NULL) {
	scan_profile(f);
	(void) fclose(f);
    }
    if ((f = fopen(option_source = prof, "r")) != NULL) {
	scan_profile(f);
	(void) fclose(f);
    }
    option_source = "Command line";
}