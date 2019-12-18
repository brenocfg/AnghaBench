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
union ctl_io {int /*<<< orphan*/  scsiio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_failover_io(union ctl_io *io, int have_lock)
{
	ctl_set_busy(&io->scsiio);
	ctl_done(io);
}