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
struct fsck_options {int* msg_type; scalar_t__ strict; } ;
typedef  enum fsck_msg_id { ____Placeholder_fsck_msg_id } fsck_msg_id ;
struct TYPE_2__ {int msg_type; } ;

/* Variables and functions */
 int FSCK_ERROR ; 
 int FSCK_MSG_MAX ; 
 int FSCK_WARN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* msg_id_info ; 

__attribute__((used)) static int fsck_msg_type(enum fsck_msg_id msg_id,
	struct fsck_options *options)
{
	int msg_type;

	assert(msg_id >= 0 && msg_id < FSCK_MSG_MAX);

	if (options->msg_type)
		msg_type = options->msg_type[msg_id];
	else {
		msg_type = msg_id_info[msg_id].msg_type;
		if (options->strict && msg_type == FSCK_WARN)
			msg_type = FSCK_ERROR;
	}

	return msg_type;
}