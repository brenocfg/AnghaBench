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
typedef  int /*<<< orphan*/  uint32_t ;
struct krb5_msg_order {int km_length; int km_jitter_window; int /*<<< orphan*/ * km_elem; } ;

/* Variables and functions */

__attribute__((used)) static void
krb5_insert_seq(struct krb5_msg_order *mo, uint32_t seq, int index)
{
	int i;

	if (mo->km_length < mo->km_jitter_window)
		mo->km_length++;

	for (i = mo->km_length - 1; i > index; i--)
		mo->km_elem[i] = mo->km_elem[i - 1];
	mo->km_elem[index] = seq;
}