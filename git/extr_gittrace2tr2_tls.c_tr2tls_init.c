#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * array_us_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_recursive_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* tr2tls_create_self (char*) ; 
 int /*<<< orphan*/  tr2tls_key ; 
 int /*<<< orphan*/  tr2tls_mutex ; 
 TYPE_1__* tr2tls_thread_main ; 
 int /*<<< orphan*/  tr2tls_us_start_main ; 

void tr2tls_init(void)
{
	pthread_key_create(&tr2tls_key, NULL);
	init_recursive_mutex(&tr2tls_mutex);

	tr2tls_thread_main = tr2tls_create_self("main");
	/*
	 * Keep a copy of the absolute start time of the main thread
	 * in a fixed variable since other threads need to access it.
	 * This also eliminates the need to lock accesses to the main
	 * thread's array (because of reallocs).
	 */
	tr2tls_us_start_main = tr2tls_thread_main->array_us_start[0];
}