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
typedef  int /*<<< orphan*/  Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SET_TP ; 
 scalar_t__ ARM_TP_ADDRESS ; 
 scalar_t__ RTLD_STATIC_TLS_EXTRA ; 
 int /*<<< orphan*/  TLS_TCB_SIZE ; 
 scalar_t__ allocate_tls (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysarch (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tls_last_offset ; 
 scalar_t__ tls_last_size ; 
 scalar_t__ tls_static_space ; 

void
allocate_initial_tls(Obj_Entry *objs)
{
#ifdef ARM_TP_ADDRESS
	void **_tp = (void **)ARM_TP_ADDRESS;
#endif

	/*
	* Fix the size of the static TLS block by using the maximum
	* offset allocated so far and adding a bit for dynamic modules to
	* use.
	*/

	tls_static_space = tls_last_offset + tls_last_size + RTLD_STATIC_TLS_EXTRA;

#ifdef ARM_TP_ADDRESS
	(*_tp) = (void *) allocate_tls(objs, NULL, TLS_TCB_SIZE, 8);
#else
	sysarch(ARM_SET_TP, allocate_tls(objs, NULL, TLS_TCB_SIZE, 8));
#endif
}