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
struct uni_msg {struct uni_msg* b_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct uni_msg*) ; 

void
uni_msg_destroy(struct uni_msg *m)
{
	free(m->b_buf);
	free(m);
}