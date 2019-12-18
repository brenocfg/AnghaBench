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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct dqblk64 {int dummy; } ;
struct dqblk32 {int dummy; } ;
typedef  int /*<<< orphan*/  dqb32 ;

/* Variables and functions */
 int _getquota (struct thread*,struct mount*,int /*<<< orphan*/ ,int,struct dqblk64*) ; 
 int copyout (struct dqblk32*,void*,int) ; 
 int /*<<< orphan*/  dqb64_dqb32 (struct dqblk64*,struct dqblk32*) ; 

int
getquota32(struct thread *td, struct mount *mp, u_long id, int type, void *addr)
{
	struct dqblk32 dqb32;
	struct dqblk64 dqb64;
	int error;

	error = _getquota(td, mp, id, type, &dqb64);
	if (error)
		return (error);
	dqb64_dqb32(&dqb64, &dqb32);
	error = copyout(&dqb32, addr, sizeof(dqb32));
	return (error);
}