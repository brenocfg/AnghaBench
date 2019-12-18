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
struct ddb_script {int /*<<< orphan*/  ds_scriptname; } ;

/* Variables and functions */
 int DB_MAXSCRIPTS ; 
 struct ddb_script* db_script_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct ddb_script *
db_script_lookup(const char *scriptname)
{
	int i;

	for (i = 0; i < DB_MAXSCRIPTS; i++) {
		if (strcmp(db_script_table[i].ds_scriptname, scriptname) ==
		    0)
			return (&db_script_table[i]);
	}
	return (NULL);
}