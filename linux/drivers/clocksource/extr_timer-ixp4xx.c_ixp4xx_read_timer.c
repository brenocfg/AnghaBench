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
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IXP4XX_OSTS_OFFSET ; 
 unsigned long __raw_readl (scalar_t__) ; 
 TYPE_1__* local_ixp4xx_timer ; 

__attribute__((used)) static unsigned long ixp4xx_read_timer(void)
{
	return __raw_readl(local_ixp4xx_timer->base + IXP4XX_OSTS_OFFSET);
}