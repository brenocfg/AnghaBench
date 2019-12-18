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
 int ENOSPC ; 
 struct ddb_script* db_script_lookup (char const*) ; 
 struct ddb_script* db_script_new () ; 
 int db_script_valid (char const*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
db_script_set(const char *scriptname, const char *script)
{
	struct ddb_script *dsp;
	int error;

	error = db_script_valid(scriptname, script);
	if (error)
		return (error);
	dsp = db_script_lookup(scriptname);
	if (dsp == NULL) {
		dsp = db_script_new();
		if (dsp == NULL)
			return (ENOSPC);
		strlcpy(dsp->ds_scriptname, scriptname,
		    sizeof(dsp->ds_scriptname));
	}
	strlcpy(dsp->ds_script, script, sizeof(dsp->ds_script));
	return (0);
}