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
typedef  int uint32_t ;
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int FSI_SMODE_ECRC ; 
 int FSI_SMODE_WSC ; 
 int fsi_smode_echodly (scalar_t__) ; 
 int fsi_smode_lbcrr (int) ; 
 int fsi_smode_senddly (scalar_t__) ; 
 int fsi_smode_sid (int) ; 

__attribute__((used)) static uint32_t fsi_slave_smode(int id, u8 t_senddly, u8 t_echodly)
{
	return FSI_SMODE_WSC | FSI_SMODE_ECRC
		| fsi_smode_sid(id)
		| fsi_smode_echodly(t_echodly - 1) | fsi_smode_senddly(t_senddly - 1)
		| fsi_smode_lbcrr(0x8);
}