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
 int /*<<< orphan*/  FPU_EAX ; 
 int no_ip_update ; 
 short status_word () ; 

__attribute__((used)) static void fstsw_ax(void)
{
	*(short *)&FPU_EAX = status_word();
	no_ip_update = 1;
}