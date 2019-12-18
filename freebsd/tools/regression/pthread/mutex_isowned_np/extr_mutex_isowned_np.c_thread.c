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
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pthread_mutex_isowned_np (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
thread(void *arg)
{
	pthread_mutex_t *mtx = arg;

	if (pthread_mutex_isowned_np(mtx) != 0) {
		printf("pthread_mutex_isowned_np() returned non-zero\n"
		    "for a mutex held by another thread\n");
		exit(1);
	}
	return (NULL);
}