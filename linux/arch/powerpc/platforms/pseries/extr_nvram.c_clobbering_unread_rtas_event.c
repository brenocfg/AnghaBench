#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ index; } ;
struct TYPE_3__ {scalar_t__ index; } ;

/* Variables and functions */
 scalar_t__ NVRAM_RTAS_READ_TIMEOUT ; 
 scalar_t__ ktime_get_real_seconds () ; 
 scalar_t__ last_unread_rtas_event ; 
 TYPE_2__ oops_log_partition ; 
 TYPE_1__ rtas_log_partition ; 

int clobbering_unread_rtas_event(void)
{
	return (oops_log_partition.index == rtas_log_partition.index
		&& last_unread_rtas_event
		&& ktime_get_real_seconds() - last_unread_rtas_event <=
						NVRAM_RTAS_READ_TIMEOUT);
}