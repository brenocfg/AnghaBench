#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct sem {int dummy; } ;
typedef  int /*<<< orphan*/  semid_t ;
typedef  TYPE_1__* sem_t ;
struct TYPE_3__ {int syssem; int /*<<< orphan*/  semid; int /*<<< orphan*/  magic; scalar_t__ nwaiters; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  SEM_MAGIC ; 
 unsigned int SEM_VALUE_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static sem_t
sem_alloc(unsigned int value, semid_t semid, int system_sem)
{
	sem_t sem;

	if (value > SEM_VALUE_MAX) {
		errno = EINVAL;
		return (NULL);
	}

	sem = (sem_t)malloc(sizeof(struct sem));
	if (sem == NULL) {
		errno = ENOSPC;
		return (NULL);
	}

	sem->count = (u_int32_t)value;
	sem->nwaiters = 0;
	sem->magic = SEM_MAGIC;
	sem->semid = semid;
	sem->syssem = system_sem;
	return (sem);
}