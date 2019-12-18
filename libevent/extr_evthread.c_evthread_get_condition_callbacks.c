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
struct evthread_condition_callbacks {int dummy; } ;

/* Variables and functions */
 struct evthread_condition_callbacks evthread_cond_fns_ ; 
 scalar_t__ evthread_lock_debugging_enabled_ ; 
 struct evthread_condition_callbacks original_cond_fns_ ; 

struct evthread_condition_callbacks *evthread_get_condition_callbacks()
{
	return evthread_lock_debugging_enabled_
	    ? &original_cond_fns_ : &evthread_cond_fns_;
}