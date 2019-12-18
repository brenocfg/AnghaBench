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
struct TYPE_2__ {scalar_t__ pri; } ;
typedef  TYPE_1__ weight_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static int
weight_compare(const void *n1, const void *n2)
{
	int32_t	k1 = ((const weight_t *)n1)->pri;
	int32_t	k2 = ((const weight_t *)n2)->pri;

	return (k1 < k2 ? -1 : k1 > k2 ? 1 : 0);
}