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
typedef  int uint8_t ;
typedef  int int8_t ;

/* Variables and functions */
 int AL_BIT (int) ; 
 int AL_SERDES_25G_RX_DIAG_SIGNED_5BIT_ABS_MASK ; 
 int AL_SERDES_25G_RX_DIAG_SIGNED_5BIT_SIGN_SHIFT ; 

__attribute__((used)) static inline void al_serdes_25g_rx_diag_5bit_signed_set(uint8_t packed_val, int8_t *ptr)
{
	uint8_t abs, sign;

	abs = packed_val & AL_SERDES_25G_RX_DIAG_SIGNED_5BIT_ABS_MASK;
	sign = (packed_val & AL_BIT(AL_SERDES_25G_RX_DIAG_SIGNED_5BIT_SIGN_SHIFT)) >>
			AL_SERDES_25G_RX_DIAG_SIGNED_5BIT_SIGN_SHIFT;
	if (sign)
		*ptr = abs;
	else
		*ptr = 0 - abs;
}