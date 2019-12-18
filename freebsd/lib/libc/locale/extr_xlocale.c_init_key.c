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
 int /*<<< orphan*/  __detect_path_locale () ; 
 int __has_thread_locale ; 
 int fake_tls ; 
 int /*<<< orphan*/  locale_info_key ; 
 void* pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xlocale_release ; 

__attribute__((used)) static void init_key(void)
{

	pthread_key_create(&locale_info_key, xlocale_release);
	pthread_setspecific(locale_info_key, (void*)42);
	if (pthread_getspecific(locale_info_key) == (void*)42) {
		pthread_setspecific(locale_info_key, 0);
	} else {
		fake_tls = 1;
	}
	/* At least one per-thread locale has now been set. */
	__has_thread_locale = 1;
	__detect_path_locale();
}