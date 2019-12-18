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
struct TYPE_2__ {scalar_t__ key; } ;
typedef  TYPE_1__ subst_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static int
subst_compare(const void *n1, const void *n2)
{
	int32_t	k1 = ((const subst_t *)n1)->key;
	int32_t	k2 = ((const subst_t *)n2)->key;

	return (k1 < k2 ? -1 : k1 > k2 ? 1 : 0);
}