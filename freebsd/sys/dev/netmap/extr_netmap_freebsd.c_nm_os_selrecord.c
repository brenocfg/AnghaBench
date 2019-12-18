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
struct thread {int dummy; } ;
struct nm_selinfo {int /*<<< orphan*/  si; } ;

/* Variables and functions */
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

void
nm_os_selrecord(struct thread *td, struct nm_selinfo *si)
{
	selrecord(td, &si->si);
}