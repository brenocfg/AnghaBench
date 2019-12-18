#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  proxy_opts; int /*<<< orphan*/  custom_headers; int /*<<< orphan*/  pb_parallelism; } ;
typedef  TYPE_2__ git_push_options ;
struct TYPE_7__ {int /*<<< orphan*/ * proxy; int /*<<< orphan*/ * custom_headers; } ;
struct TYPE_9__ {TYPE_1__ connection; int /*<<< orphan*/  pb_parallelism; } ;
typedef  TYPE_3__ git_push ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_2__ const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_PUSH_OPTIONS_VERSION ; 

int git_push_set_options(git_push *push, const git_push_options *opts)
{
	if (!push || !opts)
		return -1;

	GIT_ERROR_CHECK_VERSION(opts, GIT_PUSH_OPTIONS_VERSION, "git_push_options");

	push->pb_parallelism = opts->pb_parallelism;
	push->connection.custom_headers = &opts->custom_headers;
	push->connection.proxy = &opts->proxy_opts;

	return 0;
}