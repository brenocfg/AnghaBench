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
typedef  int /*<<< orphan*/  isc_once_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_ONCE_INIT ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_lock ; 
 scalar_t__ isc_once_do (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_strerror_lock ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 char* strerror (int) ; 
 char** sys_errlist ; 
 int sys_nerr ; 

void
isc__strerror(int num, char *buf, size_t size) {
#ifdef HAVE_STRERROR
	char *msg;
	unsigned int unum = (unsigned int)num;
	static isc_once_t once = ISC_ONCE_INIT;

	REQUIRE(buf != NULL);

	RUNTIME_CHECK(isc_once_do(&once, init_lock) == ISC_R_SUCCESS);

	LOCK(&isc_strerror_lock);
	msg = strerror(num);
	if (msg != NULL)
		snprintf(buf, size, "%s", msg);
	else
		snprintf(buf, size, "Unknown error: %u", unum);
	UNLOCK(&isc_strerror_lock);
#else
	unsigned int unum = (unsigned int)num;

	REQUIRE(buf != NULL);

	if (num >= 0 && num < sys_nerr)
		snprintf(buf, size, "%s", sys_errlist[num]);
	else
		snprintf(buf, size, "Unknown error: %u", unum);
#endif
}