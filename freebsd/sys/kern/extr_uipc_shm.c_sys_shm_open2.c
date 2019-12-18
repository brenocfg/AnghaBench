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
struct shm_open2_args {int /*<<< orphan*/  name; int /*<<< orphan*/  shmflags; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int kern_shm_open2 (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_shm_open2(struct thread *td, struct shm_open2_args *uap)
{

	return (kern_shm_open2(td, uap->path, uap->flags, uap->mode,
	    uap->shmflags, uap->name));
}