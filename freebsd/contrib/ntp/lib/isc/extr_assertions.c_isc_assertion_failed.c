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
typedef  int /*<<< orphan*/  isc_assertiontype_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  isc_assertion_failed_cb (char const*,int,int /*<<< orphan*/ ,char const*) ; 

void
isc_assertion_failed(const char *file, int line, isc_assertiontype_t type,
		     const char *cond)
{
	isc_assertion_failed_cb(file, line, type, cond);
	abort();
	/* NOTREACHED */
}