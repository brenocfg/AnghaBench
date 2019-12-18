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
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  bfd_get_filename (scalar_t__) ; 
 scalar_t__ check_kld_path (char*,size_t) ; 
 char* dirname (int /*<<< orphan*/ ) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ module_path_addr ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  target_read_string (scalar_t__,char**,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static int
find_kld_path (char *filename, char *path, size_t path_size)
{
	char *module_path;
	char *kernel_dir, *module_dir, *cp;
	int error;

	if (exec_bfd) {
		kernel_dir = dirname(bfd_get_filename(exec_bfd));
		if (kernel_dir != NULL) {
			snprintf(path, path_size, "%s/%s", kernel_dir,
			    filename);
			if (check_kld_path(path, path_size))
				return (1);
		}
	}
	if (module_path_addr != 0) {
		target_read_string(module_path_addr, &module_path, PATH_MAX,
		    &error);
		if (error == 0) {
			make_cleanup(xfree, module_path);
			cp = module_path;
			while ((module_dir = strsep(&cp, ";")) != NULL) {
				snprintf(path, path_size, "%s/%s", module_dir,
				    filename);
				if (check_kld_path(path, path_size))
					return (1);
			}
		}
	}
	return (0);
}