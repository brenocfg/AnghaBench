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
 int /*<<< orphan*/  SecureZeroMemory (void*,size_t) ; 
 int /*<<< orphan*/  explicit_bzero (void*,size_t) ; 
 int /*<<< orphan*/  explicit_memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset_s (void*,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void secure_zero_memory(void *v, size_t n)
{
#if defined(_WIN32) || defined(WIN32)
  SecureZeroMemory(v, n);
#else
// prioritize first the general C11 call
#if defined(HAVE_MEMSET_S)
  memset_s(v, n, 0, n);
#elif defined(HAVE_EXPLICIT_BZERO)
  explicit_bzero(v, n);
#elif defined(HAVE_EXPLICIT_MEMSET)
  explicit_memset(v, 0, n);
#else
  memset(v, 0, n);
  __asm__ __volatile__("" :: "r"(v) : "memory");
#endif
#endif
}