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
 int sys_hufflen ; 
 int sys_huffptr ; 
 int* sys_huffpuff ; 
 int sys_mindly ; 

void
huffpuff(void)
{
	int i;

	if (sys_huffpuff == NULL)
		return;

	sys_huffptr = (sys_huffptr + 1) % sys_hufflen;
	sys_huffpuff[sys_huffptr] = 1e9;
	sys_mindly = 1e9;
	for (i = 0; i < sys_hufflen; i++) {
		if (sys_huffpuff[i] < sys_mindly)
			sys_mindly = sys_huffpuff[i];
	}
}