#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_transport ;
struct TYPE_3__ {int member_1; void* member_2; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_smart_subtransport_definition ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  fuzzer_subtransport_cb ; 
 int git_transport_smart (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 

int fuzzer_transport_cb(git_transport **out, git_remote *owner, void *param)
{
	git_smart_subtransport_definition def = {
		fuzzer_subtransport_cb,
		1,
		param
	};
	return git_transport_smart(out, owner, &def);
}