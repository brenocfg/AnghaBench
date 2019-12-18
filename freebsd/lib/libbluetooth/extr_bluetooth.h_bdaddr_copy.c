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
struct TYPE_4__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */

__attribute__((used)) static __inline void
bdaddr_copy(bdaddr_t *d, const bdaddr_t *s)
{
	d->b[0] = s->b[0];
	d->b[1] = s->b[1];
	d->b[2] = s->b[2];
	d->b[3] = s->b[3];
	d->b[4] = s->b[4];
	d->b[5] = s->b[5];
}