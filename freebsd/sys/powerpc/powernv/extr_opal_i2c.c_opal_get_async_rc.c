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
struct opal_msg {scalar_t__ msg_type; int /*<<< orphan*/ * params; } ;

/* Variables and functions */
 scalar_t__ OPAL_MSG_ASYNC_COMP ; 
 int OPAL_PARAMETER ; 
 int htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
opal_get_async_rc(struct opal_msg msg)
{
	if (msg.msg_type != OPAL_MSG_ASYNC_COMP)
		return OPAL_PARAMETER;
	else
		return htobe64(msg.params[1]);
}