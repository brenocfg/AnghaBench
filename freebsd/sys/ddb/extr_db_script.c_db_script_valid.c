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
 scalar_t__ DB_MAXLINE ; 
 scalar_t__ DB_MAXSCRIPTLEN ; 
 scalar_t__ DB_MAXSCRIPTNAME ; 
 int EINVAL ; 
 char* db_static_buffer ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
db_script_valid(const char *scriptname, const char *script)
{
	char *buffer, *command;

	if (strlen(scriptname) == 0)
		return (EINVAL);
	if (strlen(scriptname) >= DB_MAXSCRIPTNAME)
		return (EINVAL);
	if (strlen(script) >= DB_MAXSCRIPTLEN)
		return (EINVAL);
	buffer = db_static_buffer;
	strcpy(buffer, script);
	while ((command = strsep(&buffer, ";")) != NULL) {
		if (strlen(command) >= DB_MAXLINE)
			return (EINVAL);
	}
	return (0);
}