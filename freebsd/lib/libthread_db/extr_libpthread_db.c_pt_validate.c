#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {long th_tid; TYPE_2__* th_ta; } ;
typedef  TYPE_3__ td_thrhandle_t ;
struct TYPE_6__ {TYPE_1__* map; scalar_t__ map_len; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PT_NONE ; 
 int TD_NOTHR ; 
 int TD_OK ; 

__attribute__((used)) static int
pt_validate(const td_thrhandle_t *th)
{

	if (th->th_tid < 0 || th->th_tid >= (long)th->th_ta->map_len ||
	    th->th_ta->map[th->th_tid].type == PT_NONE)
		return (TD_NOTHR);
	return (TD_OK);
}