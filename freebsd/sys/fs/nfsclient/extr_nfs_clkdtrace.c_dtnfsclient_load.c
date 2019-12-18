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
typedef  scalar_t__ dtrace_nfsclient_nfs23_start_probe_func_t ;
typedef  scalar_t__ dtrace_nfsclient_nfs23_done_probe_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PRIV_USER ; 
 int /*<<< orphan*/  dtnfsclient_attr ; 
 int /*<<< orphan*/  dtnfsclient_id ; 
 int /*<<< orphan*/  dtnfsclient_pops ; 
 scalar_t__ dtrace_nfscl_nfs234_done_probe ; 
 scalar_t__ dtrace_nfscl_nfs234_start_probe ; 
 scalar_t__ dtrace_probe ; 
 scalar_t__ dtrace_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtnfsclient_load(void *dummy)
{

	if (dtrace_register("nfscl", &dtnfsclient_attr,
	    DTRACE_PRIV_USER, NULL, &dtnfsclient_pops, NULL,
	    &dtnfsclient_id) != 0)
		return;

	dtrace_nfscl_nfs234_start_probe =
	    (dtrace_nfsclient_nfs23_start_probe_func_t)dtrace_probe;
	dtrace_nfscl_nfs234_done_probe =
	    (dtrace_nfsclient_nfs23_done_probe_func_t)dtrace_probe;
}