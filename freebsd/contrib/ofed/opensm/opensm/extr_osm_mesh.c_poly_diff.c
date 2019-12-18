#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* node; } ;
typedef  TYPE_2__ switch_t ;
struct TYPE_4__ {unsigned int num_links; int /*<<< orphan*/  poly; } ;

/* Variables and functions */
 int memcmp (int const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int poly_diff(unsigned int n, const int *p, switch_t *s)
{
	if (s->node->num_links != n)
		return 1;

	return memcmp(p, s->node->poly, n*sizeof(int));
}