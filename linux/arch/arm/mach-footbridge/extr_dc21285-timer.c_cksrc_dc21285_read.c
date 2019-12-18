#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct clocksource {scalar_t__ mask; } ;

/* Variables and functions */
 scalar_t__* CSR_TIMER2_VALUE ; 

__attribute__((used)) static u64 cksrc_dc21285_read(struct clocksource *cs)
{
	return cs->mask - *CSR_TIMER2_VALUE;
}