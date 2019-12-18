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
typedef  int isc_result_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_NET_PORTRANGEHIGH ; 
 int /*<<< orphan*/  ISC_NET_PORTRANGELOW ; 
 int ISC_R_FAILURE ; 
 int ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNUSED (int) ; 

isc_result_t
isc_net_getudpportrange(int af, in_port_t *low, in_port_t *high) {
	int result = ISC_R_FAILURE;

	REQUIRE(low != NULL && high != NULL);

	UNUSED(af);

	if (result != ISC_R_SUCCESS) {
		*low = ISC_NET_PORTRANGELOW;
		*high = ISC_NET_PORTRANGEHIGH;
	}

	return (ISC_R_SUCCESS);	/* we currently never fail in this function */
}