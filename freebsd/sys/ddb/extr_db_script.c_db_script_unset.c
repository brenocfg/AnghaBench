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
struct ddb_script {int /*<<< orphan*/  ds_script; int /*<<< orphan*/  ds_scriptname; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ddb_script* db_script_lookup (char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
db_script_unset(const char *scriptname)
{
	struct ddb_script *dsp;

	dsp = db_script_lookup(scriptname);
	if (dsp == NULL)
		return (ENOENT);
	strcpy(dsp->ds_scriptname, "");
	strcpy(dsp->ds_script, "");
	return (0);
}