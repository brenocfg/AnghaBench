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
typedef  int /*<<< orphan*/  scriptname ;

/* Variables and functions */
 int DB_MAXSCRIPTNAME ; 
 char* DB_SCRIPT_KDBENTER_DEFAULT ; 
 char* DB_SCRIPT_KDBENTER_PREFIX ; 
 scalar_t__ ENOENT ; 
 scalar_t__ db_script_exec (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

void
db_script_kdbenter(const char *eventname)
{
	char scriptname[DB_MAXSCRIPTNAME];

	snprintf(scriptname, sizeof(scriptname), "%s.%s",
	    DB_SCRIPT_KDBENTER_PREFIX, eventname);
	if (db_script_exec(scriptname, 0) == ENOENT)
		(void)db_script_exec(DB_SCRIPT_KDBENTER_DEFAULT, 0);
}