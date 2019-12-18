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
struct evthread_lock_callbacks {int dummy; } ;

/* Variables and functions */
 scalar_t__ evthread_lock_debugging_enabled_ ; 
 struct evthread_lock_callbacks evthread_lock_fns_ ; 
 struct evthread_lock_callbacks original_lock_fns_ ; 

struct evthread_lock_callbacks *evthread_get_lock_callbacks()
{
	return evthread_lock_debugging_enabled_
	    ? &original_lock_fns_ : &evthread_lock_fns_;
}