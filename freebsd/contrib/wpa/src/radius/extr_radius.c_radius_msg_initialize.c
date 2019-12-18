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
struct radius_msg {scalar_t__ attr_used; int /*<<< orphan*/  attr_size; int /*<<< orphan*/ * attr_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_DEFAULT_ATTR_COUNT ; 
 int /*<<< orphan*/ * os_calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radius_msg_initialize(struct radius_msg *msg)
{
	msg->attr_pos = os_calloc(RADIUS_DEFAULT_ATTR_COUNT,
				  sizeof(*msg->attr_pos));
	if (msg->attr_pos == NULL)
		return -1;

	msg->attr_size = RADIUS_DEFAULT_ATTR_COUNT;
	msg->attr_used = 0;

	return 0;
}