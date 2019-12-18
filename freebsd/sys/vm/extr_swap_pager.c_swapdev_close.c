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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct swdevt {int /*<<< orphan*/  sw_vp; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  VOP_CLOSE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
swapdev_close(struct thread *td, struct swdevt *sp)
{

	VOP_CLOSE(sp->sw_vp, FREAD | FWRITE, td->td_ucred, td);
	vrele(sp->sw_vp);
}