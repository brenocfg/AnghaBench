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
typedef  int uint32_t ;
struct TYPE_2__ {int (* read_cpu_ctrl ) (int) ;} ;

/* Variables and functions */
 TYPE_1__* soc_decode_win_spec ; 
 int stub1 (int) ; 

uint32_t
read_cpu_ctrl(uint32_t reg)
{

	if (soc_decode_win_spec->read_cpu_ctrl != NULL)
		return (soc_decode_win_spec->read_cpu_ctrl(reg));
	return (-1);
}