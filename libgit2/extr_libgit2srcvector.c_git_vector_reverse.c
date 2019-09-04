#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; void** contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */

void git_vector_reverse(git_vector *v)
{
	size_t a, b;

	if (v->length == 0)
		return;

	a = 0;
	b = v->length - 1;

	while (a < b) {
		void *tmp = v->contents[a];
		v->contents[a] = v->contents[b];
		v->contents[b] = tmp;
		a++;
		b--;
	}
}