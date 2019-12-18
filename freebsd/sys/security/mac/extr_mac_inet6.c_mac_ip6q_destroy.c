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
 int /*<<< orphan*/  mac_ip6q_label_free (int /*<<< orphan*/ *) ; 

void
mac_ip6q_destroy(struct ip6q *q6)
{

	if (q6->ip6q_label != NULL) {
		mac_ip6q_label_free(q6->ip6q_label);
		q6->ip6q_label = NULL;
	}
}