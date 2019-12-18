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

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  once ; 
 int /*<<< orphan*/  once3_cleanup ; 
 int /*<<< orphan*/  once3_ofunc ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
once3_threadfunc(void *arg)
{
	PTHREAD_REQUIRE(pthread_mutex_lock(&mutex));
	pthread_cleanup_push(once3_cleanup, &mutex);
	PTHREAD_REQUIRE(pthread_once(&once, once3_ofunc));
	pthread_cleanup_pop(1);

	return NULL;
}