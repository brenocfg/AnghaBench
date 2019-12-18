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
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLNX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QLNX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QL_DPRINT2 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlnx_init_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_init(void *arg)
{
	qlnx_host_t	*ha;

	ha = (qlnx_host_t *)arg;

	QL_DPRINT2(ha, "enter\n");

	QLNX_LOCK(ha);
	qlnx_init_locked(ha);
	QLNX_UNLOCK(ha);

	QL_DPRINT2(ha, "exit\n");

	return;
}