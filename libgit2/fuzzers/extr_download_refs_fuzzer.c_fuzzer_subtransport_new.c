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
struct TYPE_3__ {int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  action; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct fuzzer_subtransport {TYPE_1__ base; TYPE_2__ data; int /*<<< orphan*/ * owner; } ;
struct fuzzer_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  git_transport ;

/* Variables and functions */
 int /*<<< orphan*/  fuzzer_subtransport_action ; 
 int /*<<< orphan*/  fuzzer_subtransport_close ; 
 int /*<<< orphan*/  fuzzer_subtransport_free ; 
 struct fuzzer_subtransport* malloc (int) ; 

__attribute__((used)) static int fuzzer_subtransport_new(
	struct fuzzer_subtransport **out,
	git_transport *owner,
	const struct fuzzer_buffer *data)
{
	struct fuzzer_subtransport *sub = malloc(sizeof(*sub));
	if (!sub)
		return -1;

	sub->owner = owner;
	sub->data.data = data->data;
	sub->data.size = data->size;
	sub->base.action = fuzzer_subtransport_action;
	sub->base.close = fuzzer_subtransport_close;
	sub->base.free = fuzzer_subtransport_free;

	*out = sub;

	return 0;
}