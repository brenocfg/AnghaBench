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
struct md_req {int dummy; } ;

/* Variables and functions */
 int kern_mddetach_locked (struct thread*,struct md_req*) ; 
 int /*<<< orphan*/  md_sx ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kern_mddetach(struct thread *td, struct md_req *mdr)
{
	int error;

	sx_xlock(&md_sx);
	error = kern_mddetach_locked(td, mdr);
	sx_xunlock(&md_sx);
	return (error);
}