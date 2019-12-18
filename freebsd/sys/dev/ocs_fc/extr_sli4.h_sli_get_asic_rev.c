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
struct TYPE_3__ {int /*<<< orphan*/  asic_rev; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_asic_rev_e ;

/* Variables and functions */

__attribute__((used)) static inline sli4_asic_rev_e
sli_get_asic_rev(sli4_t *sli4)
{
	return sli4->asic_rev;
}