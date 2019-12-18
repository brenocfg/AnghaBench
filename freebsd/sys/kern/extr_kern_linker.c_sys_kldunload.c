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
struct kldunload_args {int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINKER_UNLOAD_NORMAL ; 
 int kern_kldunload (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_kldunload(struct thread *td, struct kldunload_args *uap)
{

	return (kern_kldunload(td, uap->fileid, LINKER_UNLOAD_NORMAL));
}