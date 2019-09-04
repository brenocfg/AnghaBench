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
struct mailinfo {int /*<<< orphan*/  use_scissors; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int git_default_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_mailinfo_config(const char *var, const char *value, void *mi_)
{
	struct mailinfo *mi = mi_;

	if (!starts_with(var, "mailinfo."))
		return git_default_config(var, value, NULL);
	if (!strcmp(var, "mailinfo.scissors")) {
		mi->use_scissors = git_config_bool(var, value);
		return 0;
	}
	/* perhaps others here */
	return 0;
}