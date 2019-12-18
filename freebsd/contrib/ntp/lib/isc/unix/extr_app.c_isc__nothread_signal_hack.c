#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_condition_t ;
struct TYPE_2__ {void* want_shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 void* ISC_TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_recursive_evloop ; 
 TYPE_1__ isc_g_appctx ; 
 void* signalled ; 

isc_result_t
isc__nothread_signal_hack(isc_condition_t *cp) {

	UNUSED(cp);

	INSIST(in_recursive_evloop);

	isc_g_appctx.want_shutdown = ISC_TRUE;
	signalled = ISC_TRUE;
	return (ISC_R_SUCCESS);
}