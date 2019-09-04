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
 int LAZY_MAX_MUTEX ; 
 int /*<<< orphan*/  init_recursive_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lazy_dir_mutex_array ; 
 int /*<<< orphan*/ * xcalloc (int,int) ; 

__attribute__((used)) static void init_dir_mutex(void)
{
	int j;

	lazy_dir_mutex_array = xcalloc(LAZY_MAX_MUTEX, sizeof(pthread_mutex_t));

	for (j = 0; j < LAZY_MAX_MUTEX; j++)
		init_recursive_mutex(&lazy_dir_mutex_array[j]);
}