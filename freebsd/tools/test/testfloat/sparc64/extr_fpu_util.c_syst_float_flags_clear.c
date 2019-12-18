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
typedef  int u_long ;
typedef  int int8 ;
typedef  int int32 ;
struct TYPE_2__ {int uf_fsr; } ;

/* Variables and functions */
 int FE_ALL_EXCEPT ; 
 TYPE_1__ utf ; 

int8 syst_float_flags_clear(void)
{
	int32 flags;

	flags = (utf.uf_fsr & FE_ALL_EXCEPT) >> 5;
	utf.uf_fsr &= ~(u_long)FE_ALL_EXCEPT;
	return (flags);
}