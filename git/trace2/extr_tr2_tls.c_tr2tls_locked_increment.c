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
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2tls_mutex ; 

int tr2tls_locked_increment(int *p)
{
	int current_value;

	pthread_mutex_lock(&tr2tls_mutex);
	current_value = *p;
	*p = current_value + 1;
	pthread_mutex_unlock(&tr2tls_mutex);

	return current_value;
}