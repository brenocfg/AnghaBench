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
typedef  int u_int ;
struct thread {int dummy; } ;
struct setgroups_args {int gidsetsize; int /*<<< orphan*/  gidset; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int XU_NGROUPS ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kern_setgroups (struct thread*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ngroups_max ; 

int
sys_setgroups(struct thread *td, struct setgroups_args *uap)
{
	gid_t smallgroups[XU_NGROUPS];
	gid_t *groups;
	u_int gidsetsize;
	int error;

	gidsetsize = uap->gidsetsize;
	if (gidsetsize > ngroups_max + 1)
		return (EINVAL);

	if (gidsetsize > XU_NGROUPS)
		groups = malloc(gidsetsize * sizeof(gid_t), M_TEMP, M_WAITOK);
	else
		groups = smallgroups;

	error = copyin(uap->gidset, groups, gidsetsize * sizeof(gid_t));
	if (error == 0)
		error = kern_setgroups(td, gidsetsize, groups);

	if (gidsetsize > XU_NGROUPS)
		free(groups, M_TEMP);
	return (error);
}