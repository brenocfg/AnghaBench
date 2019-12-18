#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  git_config_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tr2_sysenv_settings ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int tr2_sysenv_cb(const char *key, const char *value, void *d)
{
	int k;

	if (!starts_with(key, "trace2."))
		return 0;

	for (k = 0; k < ARRAY_SIZE(tr2_sysenv_settings); k++) {
		if (!strcmp(key, tr2_sysenv_settings[k].git_config_name)) {
			free(tr2_sysenv_settings[k].value);
			tr2_sysenv_settings[k].value = xstrdup(value);
			return 0;
		}
	}

	return 0;
}