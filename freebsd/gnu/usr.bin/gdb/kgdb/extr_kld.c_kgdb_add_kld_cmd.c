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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  check_kld_path (char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  find_kld_address (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_kld_path (char*,char*,int) ; 
 int /*<<< orphan*/  load_kld (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
kgdb_add_kld_cmd (char *arg, int from_tty)
{
	char path[PATH_MAX];
	CORE_ADDR base_addr;

	if (!exec_bfd)
		error("No kernel symbol file");

	/* Try to open the raw path to handle absolute paths first. */
	snprintf(path, sizeof(path), "%s", arg);
	if (!check_kld_path(path, sizeof(path))) {

		/*
		 * If that didn't work, look in the various possible
		 * paths for the module.
		 */
		if (!find_kld_path(arg, path, sizeof(path))) {
			error("Unable to locate kld");
			return;
		}
	}

	if (!find_kld_address(arg, &base_addr)) {
		error("Unable to find kld in kernel");
		return;
	}

	load_kld(path, base_addr, from_tty);

	reinit_frame_cache();
}