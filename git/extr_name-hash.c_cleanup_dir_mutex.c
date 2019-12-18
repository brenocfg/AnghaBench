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
 int LAZY_MAX_MUTEX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lazy_dir_mutex_array ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_dir_mutex(void)
{
	int j;

	for (j = 0; j < LAZY_MAX_MUTEX; j++)
		pthread_mutex_destroy(&lazy_dir_mutex_array[j]);

	free(lazy_dir_mutex_array);
}