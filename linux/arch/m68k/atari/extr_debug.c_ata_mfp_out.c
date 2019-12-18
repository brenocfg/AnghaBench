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
struct TYPE_2__ {int trn_stat; char usart_dta; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 TYPE_1__ st_mfp ; 

__attribute__((used)) static inline void ata_mfp_out(char c)
{
	while (!(st_mfp.trn_stat & 0x80))	/* wait for tx buf empty */
		barrier();
	st_mfp.usart_dta = c;
}