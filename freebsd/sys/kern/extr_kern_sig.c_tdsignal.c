#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_proc; } ;
struct TYPE_4__ {int ksi_signo; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  SI_KERNEL ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_1__*) ; 
 int /*<<< orphan*/  tdsendsignal (int /*<<< orphan*/ ,struct thread*,int,TYPE_1__*) ; 

void
tdsignal(struct thread *td, int sig)
{
	ksiginfo_t ksi;

	ksiginfo_init(&ksi);
	ksi.ksi_signo = sig;
	ksi.ksi_code = SI_KERNEL;
	(void) tdsendsignal(td->td_proc, td, sig, &ksi);
}