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
struct xlocale_refcounted {int dummy; } ;
typedef  scalar_t__ locale_t ;

/* Variables and functions */
 scalar_t__ LC_GLOBAL_LOCALE ; 
 int /*<<< orphan*/  __set_thread_rune_locale (scalar_t__) ; 
 scalar_t__ __thread_locale ; 
 int /*<<< orphan*/  _once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fake_tls ; 
 int /*<<< orphan*/  init_key ; 
 int /*<<< orphan*/  locale_info_key ; 
 int /*<<< orphan*/  once_control ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ thread_local_locale ; 
 int /*<<< orphan*/  xlocale_release (struct xlocale_refcounted*) ; 
 int /*<<< orphan*/  xlocale_retain (struct xlocale_refcounted*) ; 

__attribute__((used)) static void
set_thread_locale(locale_t loc)
{
	locale_t l = (loc == LC_GLOBAL_LOCALE) ? 0 : loc;

	_once(&once_control, init_key);
	
	if (NULL != l) {
		xlocale_retain((struct xlocale_refcounted*)l);
	}
	locale_t old = pthread_getspecific(locale_info_key);
	if ((NULL != old) && (l != old)) {
		xlocale_release((struct xlocale_refcounted*)old);
	}
	if (fake_tls) {
		thread_local_locale = l;
	} else {
		pthread_setspecific(locale_info_key, l);
	}
#ifndef __NO_TLS
	__thread_locale = l;
	__set_thread_rune_locale(loc);
#endif
}