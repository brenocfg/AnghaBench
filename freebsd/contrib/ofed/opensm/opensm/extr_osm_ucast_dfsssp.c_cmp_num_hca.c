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
struct TYPE_2__ {scalar_t__ num_hca; } ;
typedef  TYPE_1__ vertex_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_num_hca(const void * l1, const void * l2)
{
	vertex_t *sw1 = *((vertex_t **) l1);
	vertex_t *sw2 = *((vertex_t **) l2);
	uint32_t num_hca1 = 0, num_hca2 = 0;

	if (sw1)
		num_hca1 = sw1->num_hca;
	if (sw2)
		num_hca2 = sw2->num_hca;

	if (num_hca1 > num_hca2)
		return -1;
	else if (num_hca1 < num_hca2)
		return 1;
	else
		return 0;
}