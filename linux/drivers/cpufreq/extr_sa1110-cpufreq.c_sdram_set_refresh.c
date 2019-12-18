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
typedef  int u_int ;

/* Variables and functions */
 int MDREFR ; 

__attribute__((used)) static inline void sdram_set_refresh(u_int dri)
{
	MDREFR = (MDREFR & 0xffff000f) | (dri << 4);
	(void) MDREFR;
}