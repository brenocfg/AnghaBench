#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int sa_family; } ;
struct TYPE_6__ {TYPE_2__ sa; } ;
struct TYPE_8__ {TYPE_1__ type; } ;
typedef  TYPE_3__ isc_sockaddr_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_MSGSET_NETADDR ; 
 int /*<<< orphan*/  ISC_MSG_UNKNOWNADDR ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  isc_buffer_init (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isc_sockaddr_totext (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,char*,int) ; 

void
isc_sockaddr_format(const isc_sockaddr_t *sa, char *array, unsigned int size) {
	isc_result_t result;
	isc_buffer_t buf;

	if (size == 0U)
		return;

	isc_buffer_init(&buf, array, size);
	result = isc_sockaddr_totext(sa, &buf);
	if (result != ISC_R_SUCCESS) {
		/*
		 * The message is the same as in netaddr.c.
		 */
		snprintf(array, size,
			 "<%s %u>",
			 isc_msgcat_get(isc_msgcat, ISC_MSGSET_NETADDR,
					ISC_MSG_UNKNOWNADDR,
					"unknown address, family"),
			 sa->type.sa.sa_family);
		array[size - 1] = '\0';
	}
}