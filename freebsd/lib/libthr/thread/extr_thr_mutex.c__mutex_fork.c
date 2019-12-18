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
struct pthread {scalar_t__ robust_list; int /*<<< orphan*/ * mq; } ;

/* Variables and functions */
 size_t TMQ_NORM ; 
 size_t TMQ_NORM_PP ; 
 size_t TMQ_NORM_PP_PRIV ; 
 size_t TMQ_NORM_PRIV ; 
 size_t TMQ_ROBUST_PP ; 
 size_t TMQ_ROBUST_PP_PRIV ; 
 int /*<<< orphan*/  UMUTEX_CONTESTED ; 
 int /*<<< orphan*/  queue_fork (struct pthread*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_mutex_fork(struct pthread *curthread)
{

	queue_fork(curthread, &curthread->mq[TMQ_NORM],
	    &curthread->mq[TMQ_NORM_PRIV], 0);
	queue_fork(curthread, &curthread->mq[TMQ_NORM_PP],
	    &curthread->mq[TMQ_NORM_PP_PRIV], UMUTEX_CONTESTED);
	queue_fork(curthread, &curthread->mq[TMQ_ROBUST_PP],
	    &curthread->mq[TMQ_ROBUST_PP_PRIV], UMUTEX_CONTESTED);
	curthread->robust_list = 0;
}