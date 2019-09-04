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
struct fuzzer_subtransport {int /*<<< orphan*/  base; } ;
struct fuzzer_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  git_transport ;
typedef  int /*<<< orphan*/  git_smart_subtransport ;

/* Variables and functions */
 scalar_t__ fuzzer_subtransport_new (struct fuzzer_subtransport**,int /*<<< orphan*/ *,struct fuzzer_buffer*) ; 

int fuzzer_subtransport_cb(
	git_smart_subtransport **out,
	git_transport *owner,
	void *payload)
{
	struct fuzzer_buffer *buf = (struct fuzzer_buffer *) payload;
	struct fuzzer_subtransport *sub;

	if (fuzzer_subtransport_new(&sub, owner, buf) < 0)
		return -1;

	*out = &sub->base;
	return 0;
}