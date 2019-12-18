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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * is_ulp_fc; } ;
struct TYPE_5__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
sli_get_is_ulp_enabled(sli4_t *sli4, uint16_t ulp)
{
	return sli4->config.is_ulp_fc[ulp];
}