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
typedef  int /*<<< orphan*/ * isc_assertioncallback_t ;

/* Variables and functions */
 int /*<<< orphan*/ * default_callback ; 
 int /*<<< orphan*/ * isc_assertion_failed_cb ; 

void
isc_assertion_setcallback(isc_assertioncallback_t cb) {
	if (cb == NULL)
		isc_assertion_failed_cb = default_callback;
	else
		isc_assertion_failed_cb = cb;
}