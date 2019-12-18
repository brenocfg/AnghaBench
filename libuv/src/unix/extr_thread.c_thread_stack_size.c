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
struct rlimit {int rlim_cur; } ;
typedef  int rlim_t ;

/* Variables and functions */
 int PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 int RLIM_INFINITY ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ getpagesize () ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

__attribute__((used)) static size_t thread_stack_size(void) {
#if defined(__APPLE__) || defined(__linux__)
  struct rlimit lim;

  if (getrlimit(RLIMIT_STACK, &lim))
    abort();

  if (lim.rlim_cur != RLIM_INFINITY) {
    /* pthread_attr_setstacksize() expects page-aligned values. */
    lim.rlim_cur -= lim.rlim_cur % (rlim_t) getpagesize();

    /* Musl's PTHREAD_STACK_MIN is 2 KB on all architectures, which is
     * too small to safely receive signals on.
     *
     * Musl's PTHREAD_STACK_MIN + MINSIGSTKSZ == 8192 on arm64 (which has
     * the largest MINSIGSTKSZ of the architectures that musl supports) so
     * let's use that as a lower bound.
     *
     * We use a hardcoded value because PTHREAD_STACK_MIN + MINSIGSTKSZ
     * is between 28 and 133 KB when compiling against glibc, depending
     * on the architecture.
     */
    if (lim.rlim_cur >= 8192)
      if (lim.rlim_cur >= PTHREAD_STACK_MIN)
        return lim.rlim_cur;
  }
#endif

#if !defined(__linux__)
  return 0;
#elif defined(__PPC__) || defined(__ppc__) || defined(__powerpc__)
  return 4 << 20;  /* glibc default. */
#else
  return 2 << 20;  /* glibc default. */
#endif
}