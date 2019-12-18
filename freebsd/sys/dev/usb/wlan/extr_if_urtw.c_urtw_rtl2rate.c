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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int nitems (TYPE_1__*) ; 
 TYPE_1__* urtw_ratetable ; 

__attribute__((used)) static uint16_t
urtw_rtl2rate(uint32_t rate)
{
	unsigned int i;

	for (i = 0; i < nitems(urtw_ratetable); i++) {
		if (rate == urtw_ratetable[i].val)
			return urtw_ratetable[i].reg;
	}

	return (0);
}