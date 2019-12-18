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
struct TYPE_3__ {unsigned int PIO_SODR; unsigned int PIO_CODR; } ;
typedef  TYPE_1__* AT91PS_PIO ;

/* Variables and functions */
 TYPE_1__* AT91C_BASE_PIOB ; 

void	LED_set(unsigned int led)
{
	AT91PS_PIO	PIOB	= AT91C_BASE_PIOB;
	PIOB->PIO_SODR		= (led ^ 0x7) & 0x7;		// All 0's => Set PIO high => OFF
	PIOB->PIO_CODR		=  led & 0x7;			// All 1's => Set PIO low   => ON
}