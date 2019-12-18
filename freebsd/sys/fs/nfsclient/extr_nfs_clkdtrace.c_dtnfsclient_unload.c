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
 int /*<<< orphan*/  dtnfsclient_id ; 
 int /*<<< orphan*/ * dtrace_nfscl_nfs234_done_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_nfs234_start_probe ; 
 int dtrace_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtnfsclient_unload()
{

	dtrace_nfscl_nfs234_start_probe = NULL;
	dtrace_nfscl_nfs234_done_probe = NULL;

	return (dtrace_unregister(dtnfsclient_id));
}