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
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2tls_key ; 
 int /*<<< orphan*/  tr2tls_mutex ; 
 int /*<<< orphan*/ * tr2tls_thread_main ; 
 int /*<<< orphan*/  tr2tls_unset_self () ; 

void tr2tls_release(void)
{
	tr2tls_unset_self();
	tr2tls_thread_main = NULL;

	pthread_mutex_destroy(&tr2tls_mutex);
	pthread_key_delete(tr2tls_key);
}