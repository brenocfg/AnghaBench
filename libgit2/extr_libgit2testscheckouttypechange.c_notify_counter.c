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
struct TYPE_2__ {int /*<<< orphan*/  ignored; int /*<<< orphan*/  untracked; int /*<<< orphan*/  updates; int /*<<< orphan*/  dirty; int /*<<< orphan*/  conflicts; } ;
typedef  TYPE_1__ notify_counts ;
typedef  char git_diff_file ;
typedef  int git_checkout_notify_t ;

/* Variables and functions */
#define  GIT_CHECKOUT_NOTIFY_CONFLICT 132 
#define  GIT_CHECKOUT_NOTIFY_DIRTY 131 
#define  GIT_CHECKOUT_NOTIFY_IGNORED 130 
#define  GIT_CHECKOUT_NOTIFY_UNTRACKED 129 
#define  GIT_CHECKOUT_NOTIFY_UPDATED 128 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 

__attribute__((used)) static int notify_counter(
	git_checkout_notify_t why,
	const char *path,
	const git_diff_file *baseline,
	const git_diff_file *target,
	const git_diff_file *workdir,
	void *payload)
{
	notify_counts *cts = payload;

	GIT_UNUSED(path);
	GIT_UNUSED(baseline);
	GIT_UNUSED(target);
	GIT_UNUSED(workdir);

	switch (why) {
	case GIT_CHECKOUT_NOTIFY_CONFLICT:  cts->conflicts++; break;
	case GIT_CHECKOUT_NOTIFY_DIRTY:     cts->dirty++;     break;
	case GIT_CHECKOUT_NOTIFY_UPDATED:   cts->updates++;   break;
	case GIT_CHECKOUT_NOTIFY_UNTRACKED: cts->untracked++; break;
	case GIT_CHECKOUT_NOTIFY_IGNORED:   cts->ignored++;   break;
	default: break;
	}

	return 0;
}