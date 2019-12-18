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

/* Variables and functions */
 int /*<<< orphan*/  ISC_MSGSET_GENERAL ; 
 int /*<<< orphan*/  ISC_MSG_FAILED ; 
 int /*<<< orphan*/  isc_error_fatal (char const*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 int /*<<< orphan*/  isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
isc_error_runtimecheck(const char *file, int line, const char *expression) {
	isc_error_fatal(file, line, "RUNTIME_CHECK(%s) %s", expression,
			isc_msgcat_get(isc_msgcat, ISC_MSGSET_GENERAL,
				       ISC_MSG_FAILED, "failed"));
}