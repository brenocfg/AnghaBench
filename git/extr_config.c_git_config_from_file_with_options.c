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
struct config_options {int dummy; } ;
typedef  int /*<<< orphan*/  config_fn_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ORIGIN_FILE ; 
 int do_config_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,void*,struct config_options const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char const*,char*) ; 

int git_config_from_file_with_options(config_fn_t fn, const char *filename,
				      void *data,
				      const struct config_options *opts)
{
	int ret = -1;
	FILE *f;

	f = fopen_or_warn(filename, "r");
	if (f) {
		ret = do_config_from_file(fn, CONFIG_ORIGIN_FILE, filename,
					  filename, f, data, opts);
		fclose(f);
	}
	return ret;
}