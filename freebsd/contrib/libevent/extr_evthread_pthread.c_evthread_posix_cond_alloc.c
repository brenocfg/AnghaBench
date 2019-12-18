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
typedef  void pthread_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  mm_free (void*) ; 
 void* mm_malloc (int) ; 
 scalar_t__ pthread_cond_init (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
evthread_posix_cond_alloc(unsigned condflags)
{
	pthread_cond_t *cond = mm_malloc(sizeof(pthread_cond_t));
	if (!cond)
		return NULL;
	if (pthread_cond_init(cond, NULL)) {
		mm_free(cond);
		return NULL;
	}
	return cond;
}