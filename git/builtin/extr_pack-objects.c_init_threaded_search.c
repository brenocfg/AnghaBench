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
 int /*<<< orphan*/  cache_mutex ; 
 int /*<<< orphan*/  progress_cond ; 
 int /*<<< orphan*/  progress_mutex ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_threaded_search(void)
{
	pthread_mutex_init(&cache_mutex, NULL);
	pthread_mutex_init(&progress_mutex, NULL);
	pthread_cond_init(&progress_cond, NULL);
}