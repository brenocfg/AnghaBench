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
struct TYPE_3__ {scalar_t__ id; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
struct ib_umad_packet {int /*<<< orphan*/  list; TYPE_2__ mad; } ;
struct ib_umad_file {int /*<<< orphan*/  mutex; int /*<<< orphan*/  recv_wait; int /*<<< orphan*/  recv_list; } ;
struct ib_mad_agent {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_UMAD_MAX_AGENTS ; 
 struct ib_mad_agent* __get_agent (struct ib_umad_file*,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int queue_packet(struct ib_umad_file *file,
			struct ib_mad_agent *agent,
			struct ib_umad_packet *packet)
{
	int ret = 1;

	mutex_lock(&file->mutex);

	for (packet->mad.hdr.id = 0;
	     packet->mad.hdr.id < IB_UMAD_MAX_AGENTS;
	     packet->mad.hdr.id++)
		if (agent == __get_agent(file, packet->mad.hdr.id)) {
			list_add_tail(&packet->list, &file->recv_list);
			wake_up_interruptible(&file->recv_wait);
			ret = 0;
			break;
		}

	mutex_unlock(&file->mutex);

	return ret;
}