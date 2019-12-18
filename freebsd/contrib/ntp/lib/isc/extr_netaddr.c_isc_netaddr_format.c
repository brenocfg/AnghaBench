#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_4__ {int family; } ;
typedef  TYPE_1__ isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_MSGSET_NETADDR ; 
 int /*<<< orphan*/  ISC_MSG_UNKNOWNADDR ; 
 scalar_t__ ISC_R_NOSPACE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int isc_buffer_availablelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_init (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  isc_buffer_putuint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isc_netaddr_totext (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char*,int) ; 

void
isc_netaddr_format(const isc_netaddr_t *na, char *array, unsigned int size) {
	isc_result_t result;
	isc_buffer_t buf;

	isc_buffer_init(&buf, array, size);
	result = isc_netaddr_totext(na, &buf);

	if (size == 0)
		return;

	/*
	 * Null terminate.
	 */
	if (result == ISC_R_SUCCESS) {
		if (isc_buffer_availablelength(&buf) >= 1)
			isc_buffer_putuint8(&buf, 0);
		else
			result = ISC_R_NOSPACE;
	}

	if (result != ISC_R_SUCCESS) {
		snprintf(array, size,
			 "<%s %u>",
			 isc_msgcat_get(isc_msgcat, ISC_MSGSET_NETADDR,
					ISC_MSG_UNKNOWNADDR,
					"unknown address, family"),
			 na->family);
		array[size - 1] = '\0';
	}
}