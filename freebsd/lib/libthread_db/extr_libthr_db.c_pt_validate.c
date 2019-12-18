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
struct TYPE_3__ {scalar_t__ th_tid; scalar_t__ th_thread; } ;
typedef  TYPE_1__ td_thrhandle_t ;

/* Variables and functions */
 int TD_ERR ; 
 int TD_OK ; 

__attribute__((used)) static int
pt_validate(const td_thrhandle_t *th)
{

	if (th->th_tid == 0 || th->th_thread == 0)
		return (TD_ERR);
	return (TD_OK);
}