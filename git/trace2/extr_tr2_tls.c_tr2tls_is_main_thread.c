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
 int /*<<< orphan*/  HAVE_THREADS ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2tls_key ; 
 scalar_t__ tr2tls_thread_main ; 

int tr2tls_is_main_thread(void)
{
	if (!HAVE_THREADS)
		return 1;

	return pthread_getspecific(tr2tls_key) == tr2tls_thread_main;
}