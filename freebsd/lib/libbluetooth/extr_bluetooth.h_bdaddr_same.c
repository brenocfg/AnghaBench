#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* b; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */

__attribute__((used)) static __inline int
bdaddr_same(const bdaddr_t *a, const bdaddr_t *b)
{
	return (a->b[0] == b->b[0] && a->b[1] == b->b[1] &&
		a->b[2] == b->b[2] && a->b[3] == b->b[3] &&
		a->b[4] == b->b[4] && a->b[5] == b->b[5]);
}