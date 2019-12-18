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
 int NOTIFY_DONE ; 
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*) ; 
 int /*<<< orphan*/  crypto_chain ; 
 int /*<<< orphan*/  request_module (char*) ; 

int crypto_probing_notify(unsigned long val, void *v)
{
	int ok;

	ok = blocking_notifier_call_chain(&crypto_chain, val, v);
	if (ok == NOTIFY_DONE) {
		request_module("cryptomgr");
		ok = blocking_notifier_call_chain(&crypto_chain, val, v);
	}

	return ok;
}