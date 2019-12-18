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
struct TYPE_2__ {scalar_t__ kd_length; } ;
struct krb5_keyblock {TYPE_1__ kk_key; } ;

/* Variables and functions */

__attribute__((used)) static void
copy_key(struct krb5_keyblock *from, struct krb5_keyblock **to)
{

	if (from->kk_key.kd_length)
		*to = from;
	else
		*to = NULL;
}