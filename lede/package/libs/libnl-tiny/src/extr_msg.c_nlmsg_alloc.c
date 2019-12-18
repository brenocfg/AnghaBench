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
struct nl_msg {int dummy; } ;

/* Variables and functions */
 struct nl_msg* __nlmsg_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_msg_size ; 

struct nl_msg *nlmsg_alloc(void)
{
	return __nlmsg_alloc(default_msg_size);
}