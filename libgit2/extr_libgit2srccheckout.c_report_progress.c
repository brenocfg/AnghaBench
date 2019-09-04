#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  progress_payload; int /*<<< orphan*/  (* progress_cb ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ opts; int /*<<< orphan*/  total_steps; int /*<<< orphan*/  completed_steps; } ;
typedef  TYPE_2__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_progress(
	checkout_data *data,
	const char *path)
{
	if (data->opts.progress_cb)
		data->opts.progress_cb(
			path, data->completed_steps, data->total_steps,
			data->opts.progress_payload);
}