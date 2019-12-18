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
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 unsigned int randombytes_uniform (unsigned int) ; 
 int /*<<< orphan*/  segv_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sodium_free (void*) ; 
 void* sodium_malloc (size_t) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  sodium_mprotect_noaccess (void*) ; 
 int /*<<< orphan*/  sodium_mprotect_readonly (void*) ; 
 int /*<<< orphan*/  sodium_mprotect_readwrite (void*) ; 

int
main(void)
{
    void * buf;
    size_t size;

#ifdef SIGSEGV
    signal(SIGSEGV, segv_handler);
#endif
#ifdef SIGBUS
    signal(SIGBUS, segv_handler);
#endif
#ifdef SIGABRT
    signal(SIGABRT, segv_handler);
#endif
    size = 1U + randombytes_uniform(100000U);
    buf  = sodium_malloc(size);
    assert(buf != NULL);

/* old versions of asan emit a warning because they don't support mlock*() */
#ifndef __SANITIZE_ADDRESS__
    sodium_mprotect_noaccess(buf);
    sodium_mprotect_readwrite(buf);
#endif

#if defined(HAVE_CATCHABLE_SEGV) && !defined(__EMSCRIPTEN__) && !defined(__SANITIZE_ADDRESS__)
    sodium_memzero(((unsigned char *) buf) - 8, 8U);
    sodium_mprotect_readonly(buf);
    sodium_free(buf);
    printf("Underflow not caught\n");
#else
    segv_handler(0);
#endif
    return 0;
}