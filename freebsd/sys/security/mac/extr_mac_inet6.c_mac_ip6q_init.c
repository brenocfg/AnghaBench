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
struct ip6q {int /*<<< orphan*/ * ip6q_label; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MPC_OBJECT_IP6Q ; 
 int /*<<< orphan*/ * mac_ip6q_label_alloc (int) ; 
 int mac_labeled ; 

int
mac_ip6q_init(struct ip6q *q6, int flag)
{

	if (mac_labeled & MPC_OBJECT_IP6Q) {
		q6->ip6q_label = mac_ip6q_label_alloc(flag);
		if (q6->ip6q_label == NULL)
			return (ENOMEM);
	} else
		q6->ip6q_label = NULL;
	return (0);
}