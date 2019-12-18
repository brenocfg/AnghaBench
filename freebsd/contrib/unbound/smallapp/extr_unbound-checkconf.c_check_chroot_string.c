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
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 char* fname_after_chroot (char*,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_file (char*) ; 

__attribute__((used)) static void
check_chroot_string(const char* desc, char** ss,
	const char* chrootdir, struct config_file* cfg)
{
	char* str = *ss;
	if(str && str[0]) {
		*ss = fname_after_chroot(str, cfg, 1);
		if(!*ss) fatal_exit("out of memory");
		if(!is_file(*ss)) {
			if(chrootdir && chrootdir[0])
				fatal_exit("%s: \"%s\" does not exist in "
					"chrootdir %s", desc, str, chrootdir);
			else
				fatal_exit("%s: \"%s\" does not exist",
					desc, str);
		}
		/* put in a new full path for continued checking */
		free(str);
	}
}