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
struct TYPE_2__ {int /*<<< orphan*/  downcased; } ;

/* Variables and functions */
 int FSCK_MSG_MAX ; 
 TYPE_1__* msg_id_info ; 
 int /*<<< orphan*/  prepare_msg_ids () ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_msg_id(const char *text)
{
	int i;

	prepare_msg_ids();

	for (i = 0; i < FSCK_MSG_MAX; i++)
		if (!strcmp(text, msg_id_info[i].downcased))
			return i;

	return -1;
}