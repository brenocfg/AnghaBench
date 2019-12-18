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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ plcp; scalar_t__ rate; } ;

/* Variables and functions */
 int IWM_RIDX_MAX ; 
 TYPE_1__* iwm_rates ; 

__attribute__((used)) static uint8_t
iwm_rate_from_ucode_rate(uint32_t rate_n_flags)
{
	uint8_t plcp = rate_n_flags & 0xff;
	int i;

	for (i = 0; i <= IWM_RIDX_MAX; i++) {
		if (iwm_rates[i].plcp == plcp)
			return iwm_rates[i].rate;
	}
	return 0;
}