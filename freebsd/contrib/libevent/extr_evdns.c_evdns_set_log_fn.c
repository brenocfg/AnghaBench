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
typedef  int /*<<< orphan*/  evdns_debug_log_fn_type ;

/* Variables and functions */
 int /*<<< orphan*/  evdns_log_fn ; 

void
evdns_set_log_fn(evdns_debug_log_fn_type fn)
{
	evdns_log_fn = fn;
}