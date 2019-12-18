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
struct thread {int /*<<< orphan*/  td_proc; } ;
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  tdsendsignal (int /*<<< orphan*/ ,struct thread*,int,int /*<<< orphan*/ *) ; 

void
tdksignal(struct thread *td, int sig, ksiginfo_t *ksi)
{

	(void) tdsendsignal(td->td_proc, td, sig, ksi);
}