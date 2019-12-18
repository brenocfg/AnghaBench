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
 int /*<<< orphan*/  init_recursive_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tr2tls_create_self (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2tls_key ; 
 int /*<<< orphan*/  tr2tls_mutex ; 
 int /*<<< orphan*/  tr2tls_start_process_clock () ; 
 int /*<<< orphan*/  tr2tls_thread_main ; 
 int /*<<< orphan*/  tr2tls_us_start_process ; 

void tr2tls_init(void)
{
	tr2tls_start_process_clock();

	pthread_key_create(&tr2tls_key, NULL);
	init_recursive_mutex(&tr2tls_mutex);

	tr2tls_thread_main =
		tr2tls_create_self("main", tr2tls_us_start_process);
}