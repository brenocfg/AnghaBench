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
struct fsck_options {int* msg_type; } ;
struct TYPE_2__ {scalar_t__ msg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int*,int) ; 
 int FSCK_ERROR ; 
 scalar_t__ FSCK_FATAL ; 
 int FSCK_MSG_MAX ; 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 int fsck_msg_type (int,struct fsck_options*) ; 
 TYPE_1__* msg_id_info ; 
 int parse_msg_id (char const*) ; 
 int parse_msg_type (char const*) ; 

void fsck_set_msg_type(struct fsck_options *options,
		const char *msg_id, const char *msg_type)
{
	int id = parse_msg_id(msg_id), type;

	if (id < 0)
		die("Unhandled message id: %s", msg_id);
	type = parse_msg_type(msg_type);

	if (type != FSCK_ERROR && msg_id_info[id].msg_type == FSCK_FATAL)
		die("Cannot demote %s to %s", msg_id, msg_type);

	if (!options->msg_type) {
		int i;
		int *msg_type;
		ALLOC_ARRAY(msg_type, FSCK_MSG_MAX);
		for (i = 0; i < FSCK_MSG_MAX; i++)
			msg_type[i] = fsck_msg_type(i, options);
		options->msg_type = msg_type;
	}

	options->msg_type[id] = type;
}