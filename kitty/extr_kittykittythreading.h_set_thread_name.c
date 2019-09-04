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
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setname_np (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline void
set_thread_name(const char *name) {
    int ret;
#if defined(__APPLE__)
    ret = pthread_setname_np(name);
#elif defined(FREEBSD_SET_NAME)
    pthread_set_name_np(pthread_self(), name);
    ret = 0;
#else
    ret = pthread_setname_np(pthread_self(), name);
#endif
    if (ret != 0) perror("Failed to set thread name");
}