#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ chmod_calls; scalar_t__ stat_calls; scalar_t__ mkdir_calls; } ;
struct git_futils_mkdir_options {TYPE_2__ perfdata; int /*<<< orphan*/ * pool; int /*<<< orphan*/  dir_map; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_5__ {int /*<<< orphan*/  chmod_calls; int /*<<< orphan*/  stat_calls; int /*<<< orphan*/  mkdir_calls; } ;
struct TYPE_7__ {TYPE_1__ perfdata; int /*<<< orphan*/  pool; int /*<<< orphan*/  mkdir_map; } ;
typedef  TYPE_3__ checkout_data ;

/* Variables and functions */
 int git_futils_mkdir_relative (char const*,char const*,int /*<<< orphan*/ ,unsigned int,struct git_futils_mkdir_options*) ; 

__attribute__((used)) static int checkout_mkdir(
	checkout_data *data,
	const char *path,
	const char *base,
	mode_t mode,
	unsigned int flags)
{
	struct git_futils_mkdir_options mkdir_opts = {0};
	int error;

	mkdir_opts.dir_map = data->mkdir_map;
	mkdir_opts.pool = &data->pool;

	error = git_futils_mkdir_relative(
		path, base, mode, flags, &mkdir_opts);

	data->perfdata.mkdir_calls += mkdir_opts.perfdata.mkdir_calls;
	data->perfdata.stat_calls += mkdir_opts.perfdata.stat_calls;
	data->perfdata.chmod_calls += mkdir_opts.perfdata.chmod_calls;

	return error;
}