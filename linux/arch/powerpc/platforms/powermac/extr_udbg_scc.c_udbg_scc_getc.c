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
 int SCC_RXRDY ; 
 int in_8 (scalar_t__) ; 
 scalar_t__ sccc ; 
 scalar_t__ sccd ; 

__attribute__((used)) static int udbg_scc_getc(void)
{
	if (sccc) {
		while ((in_8(sccc) & SCC_RXRDY) == 0)
			;
		return in_8(sccd);
	}
	return -1;
}