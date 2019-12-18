#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct prison {int dummy; } ;
typedef  scalar_t__ key_t ;
struct TYPE_5__ {int mode; scalar_t__ key; } ;
struct TYPE_6__ {TYPE_1__ shm_perm; } ;
struct TYPE_8__ {TYPE_2__ u; TYPE_3__* cred; } ;
struct TYPE_7__ {struct prison* cr_prison; } ;

/* Variables and functions */
 int SHMSEG_ALLOCATED ; 
 int shmalloced ; 
 TYPE_4__* shmsegs ; 

__attribute__((used)) static int
shm_find_segment_by_key(struct prison *pr, key_t key)
{
	int i;

	for (i = 0; i < shmalloced; i++)
		if ((shmsegs[i].u.shm_perm.mode & SHMSEG_ALLOCATED) &&
		    shmsegs[i].cred != NULL &&
		    shmsegs[i].cred->cr_prison == pr &&
		    shmsegs[i].u.shm_perm.key == key)
			return (i);
	return (-1);
}