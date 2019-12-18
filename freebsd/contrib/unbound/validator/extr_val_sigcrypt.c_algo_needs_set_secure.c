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
typedef  size_t uint8_t ;
struct algo_needs {scalar_t__ num; scalar_t__* needs; } ;

/* Variables and functions */

int algo_needs_set_secure(struct algo_needs* n, uint8_t algo)
{
	if(n->needs[algo]) {
		n->needs[algo] = 0;
		n->num --;
		if(n->num == 0) /* done! */
			return 1;
	}
	return 0;
}