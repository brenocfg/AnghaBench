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

/* Variables and functions */
 scalar_t__ MACHINE_HAS_GS ; 
 scalar_t__ MACHINE_HAS_VX ; 

__attribute__((used)) static inline int nmi_needs_mcesa(void)
{
	return MACHINE_HAS_VX || MACHINE_HAS_GS;
}