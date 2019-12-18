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
typedef  int /*<<< orphan*/  isc__socketmgr_t ;

/* Variables and functions */
 int SELECT_POKE_SHUTDOWN ; 
 int /*<<< orphan*/  wakeup_socket (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
select_poke(isc__socketmgr_t *manager, int fd, int msg) {
	if (msg == SELECT_POKE_SHUTDOWN)
		return;
	else if (fd >= 0)
		wakeup_socket(manager, fd, msg);
	return;
}