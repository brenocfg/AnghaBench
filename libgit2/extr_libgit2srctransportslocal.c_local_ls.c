#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t length; scalar_t__ contents; } ;
struct TYPE_4__ {TYPE_1__ refs; int /*<<< orphan*/  have_refs; } ;
typedef  TYPE_2__ transport_local ;
typedef  int /*<<< orphan*/  git_transport ;
typedef  int /*<<< orphan*/  git_remote_head ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int local_ls(const git_remote_head ***out, size_t *size, git_transport *transport)
{
	transport_local *t = (transport_local *)transport;

	if (!t->have_refs) {
		git_error_set(GIT_ERROR_NET, "the transport has not yet loaded the refs");
		return -1;
	}

	*out = (const git_remote_head **)t->refs.contents;
	*size = t->refs.length;

	return 0;
}