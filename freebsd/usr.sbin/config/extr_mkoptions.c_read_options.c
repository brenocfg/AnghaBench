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
 int MAXPATHLEN ; 
 int /*<<< orphan*/  OL_ALIAS ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 char* machinename ; 
 int /*<<< orphan*/  otab ; 
 int /*<<< orphan*/  read_option_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
read_options(void)
{
	char fname[MAXPATHLEN];

	SLIST_INIT(&otab);
	read_option_file("../../conf/options", 0);
	(void)snprintf(fname, sizeof fname, "../../conf/options.%s",
	    machinename);
	if (!read_option_file(fname, 0)) {
		(void)snprintf(fname, sizeof fname, "options.%s", machinename);
		read_option_file(fname, 0);
	}
	read_option_file("../../conf/options-compat", OL_ALIAS);
}