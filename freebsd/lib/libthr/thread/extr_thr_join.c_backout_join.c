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
struct pthread {int /*<<< orphan*/ * joiner; } ;

/* Variables and functions */
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 struct pthread* _get_curthread () ; 

__attribute__((used)) static void backout_join(void *arg)
{
	struct pthread *pthread = (struct pthread *)arg;
	struct pthread *curthread = _get_curthread();

	THR_THREAD_LOCK(curthread, pthread);
	pthread->joiner = NULL;
	THR_THREAD_UNLOCK(curthread, pthread);
}