#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * file; } ;
struct config_source {int origin_type; char const* name; char const* path; int /*<<< orphan*/  do_ftell; int /*<<< orphan*/  do_ungetc; int /*<<< orphan*/  do_fgetc; int /*<<< orphan*/  default_error_action; TYPE_1__ u; } ;
struct config_options {int dummy; } ;
typedef  enum config_origin_type { ____Placeholder_config_origin_type } config_origin_type ;
typedef  int /*<<< orphan*/  config_fn_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ERROR_DIE ; 
 int /*<<< orphan*/  config_file_fgetc ; 
 int /*<<< orphan*/  config_file_ftell ; 
 int /*<<< orphan*/  config_file_ungetc ; 
 int do_config_from (struct config_source*,int /*<<< orphan*/ ,void*,struct config_options const*) ; 
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_config_from_file(config_fn_t fn,
		const enum config_origin_type origin_type,
		const char *name, const char *path, FILE *f,
		void *data, const struct config_options *opts)
{
	struct config_source top;
	int ret;

	top.u.file = f;
	top.origin_type = origin_type;
	top.name = name;
	top.path = path;
	top.default_error_action = CONFIG_ERROR_DIE;
	top.do_fgetc = config_file_fgetc;
	top.do_ungetc = config_file_ungetc;
	top.do_ftell = config_file_ftell;

	flockfile(f);
	ret = do_config_from(&top, fn, data, opts);
	funlockfile(f);
	return ret;
}