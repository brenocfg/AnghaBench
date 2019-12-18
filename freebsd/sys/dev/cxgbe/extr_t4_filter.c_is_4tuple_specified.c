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
struct TYPE_2__ {int sport; int dport; int* sip; int* dip; } ;
struct t4_filter_specification {TYPE_1__ mask; scalar_t__ type; } ;

/* Variables and functions */

__attribute__((used)) static bool
is_4tuple_specified(struct t4_filter_specification *fs)
{
	int i;
	const int n = fs->type ? 16 : 4;

	if (fs->mask.sport != 0xffff || fs->mask.dport != 0xffff)
		return (false);

	for (i = 0; i < n; i++) {
		if (fs->mask.sip[i] != 0xff)
			return (false);
		if (fs->mask.dip[i] != 0xff)
			return (false);
	}

	return (true);
}