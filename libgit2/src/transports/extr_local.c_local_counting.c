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
struct TYPE_2__ {int (* progress_cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  message_cb_payload; } ;
typedef  TYPE_1__ transport_local ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_PACKBUILDER_ADDING_OBJECTS ; 
 int GIT_PACKBUILDER_DELTAFICATION ; 
 int /*<<< orphan*/  compressing_objects_fmt ; 
 int /*<<< orphan*/  counting_objects_fmt ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int local_counting(int stage, unsigned int current, unsigned int total, void *payload)
{
	git_buf progress_info = GIT_BUF_INIT;
	transport_local *t = payload;
	int error;

	if (!t->progress_cb)
		return 0;

	if (stage == GIT_PACKBUILDER_ADDING_OBJECTS) {
		git_buf_printf(&progress_info, counting_objects_fmt, current);
	} else if (stage == GIT_PACKBUILDER_DELTAFICATION) {
		float perc = (((float) current) / total) * 100;
		git_buf_printf(&progress_info, compressing_objects_fmt, perc, current, total);
		if (current == total)
			git_buf_printf(&progress_info, ", done\n");
		else
			git_buf_putc(&progress_info, '\r');

	}

	if (git_buf_oom(&progress_info))
		return -1;

	error = t->progress_cb(git_buf_cstr(&progress_info), (int)git_buf_len(&progress_info), t->message_cb_payload);
	git_buf_dispose(&progress_info);

	return error;
}