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
 struct nl_msg* __nlmsg_alloc (size_t) ; 

struct nl_msg *nlmsg_alloc_size(size_t max)
{
	return __nlmsg_alloc(max);
}