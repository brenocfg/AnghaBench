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
typedef  int /*<<< orphan*/ * isc_errorcallback_t ;

/* Variables and functions */
 int /*<<< orphan*/ * default_unexpected_callback ; 
 int /*<<< orphan*/ * unexpected_callback ; 

void
isc_error_setunexpected(isc_errorcallback_t cb) {
	if (cb == NULL)
		unexpected_callback = default_unexpected_callback;
	else
		unexpected_callback = cb;
}