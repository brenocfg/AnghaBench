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
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kgss_gssd_handle ; 
 int /*<<< orphan*/  kgss_gssd_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

CLIENT *
kgss_gssd_client(void)
{
	CLIENT *cl;

	mtx_lock(&kgss_gssd_lock);
	cl = kgss_gssd_handle;
	if (cl != NULL)
		CLNT_ACQUIRE(cl);
	mtx_unlock(&kgss_gssd_lock);
	return (cl);
}