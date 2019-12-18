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
struct sigio {int /*<<< orphan*/  sio_pgid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGIO_LOCK () ; 
 int /*<<< orphan*/  SIGIO_UNLOCK () ; 

pid_t
fgetown(struct sigio **sigiop)
{
	pid_t pgid;

	SIGIO_LOCK();
	pgid = (*sigiop != NULL) ? (*sigiop)->sio_pgid : 0;
	SIGIO_UNLOCK();
	return (pgid);
}