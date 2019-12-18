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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ match_last_path_component (char*,size_t*,char*) ; 
 char* path_lookup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int is_msys2_sh(const char *cmd)
{
	if (cmd && !strcmp(cmd, "sh")) {
		static int ret = -1;
		char *p;

		if (ret >= 0)
			return ret;

		p = path_lookup(cmd, 0);
		if (!p)
			ret = 0;
		else {
			size_t len = strlen(p);

			ret = match_last_path_component(p, &len, "sh.exe") &&
				match_last_path_component(p, &len, "bin") &&
				match_last_path_component(p, &len, "usr");
			free(p);
		}
		return ret;
	}
	return 0;
}