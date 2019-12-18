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
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGSEGV ; 
 unsigned int SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ memcmp (void*,void*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,unsigned int,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  randombytes_buf (void*,size_t) ; 
 unsigned int randombytes_uniform (unsigned int) ; 
 int /*<<< orphan*/  segv_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 void* sodium_allocarray (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sodium_free (void*) ; 
 void* sodium_malloc (size_t) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  sodium_mprotect_noaccess (void*) ; 
 int /*<<< orphan*/  sodium_mprotect_readonly (void*) ; 
 int /*<<< orphan*/  sodium_mprotect_readwrite (void*) ; 
 scalar_t__ sodium_mshield (void*) ; 
 scalar_t__ sodium_munshield (void*) ; 

int
main(void)
{
    void         *buf;
    void         *buf2;
    size_t        size;
    unsigned int  i;

    size = randombytes_uniform(100U);
    if ((buf = sodium_malloc(size)) == NULL ||
        (buf2 = sodium_malloc(size)) == NULL) {
        return 1;
    }
    randombytes_buf(buf, size);
    memcpy(buf2, buf, size);
    errno = EINVAL;
    if (sodium_mshield(buf) != 0) {
        assert(errno == ENOSYS);
    } else {
        assert(size == 0U || memcmp(buf, buf2, size) != 0);
    }
    errno = EINVAL;
    if (sodium_munshield(buf) != 0) {
        assert(errno == ENOSYS);
    } else {
        assert(size == 0U || memcmp(buf, buf2, size) == 0);
    }
    sodium_free(buf2);
    sodium_free(buf);

    if (sodium_malloc(SIZE_MAX - 1U) != NULL) {
        return 1;
    }
    if (sodium_malloc(0U) == NULL) {
        return 1;
    }
    if (sodium_allocarray(SIZE_MAX / 2U + 1U, SIZE_MAX / 2U) != NULL) {
        return 1;
    }
    sodium_free(sodium_allocarray(0U, 0U));
    sodium_free(sodium_allocarray(0U, 1U));
    sodium_free(sodium_allocarray(1U, 0U));

    buf = sodium_allocarray(1000U, 50U);
    memset(buf, 0, 50000U);
    sodium_free(buf);

    sodium_free(sodium_malloc(0U));
    sodium_free(NULL);
    for (i = 0U; i < 10000U; i++) {
        size = 1U + randombytes_uniform(100000U);
        buf  = sodium_malloc(size);
        assert(buf != NULL);
        memset(buf, i, size);
        sodium_mprotect_noaccess(buf);
        sodium_free(buf);
    }
    printf("OK\n");
#ifdef SIG_DFL
# ifdef SIGSEGV
    signal(SIGSEGV, segv_handler);
# endif
# ifdef SIGBUS
    signal(SIGBUS, segv_handler);
# endif
# ifdef SIGABRT
    signal(SIGABRT, segv_handler);
# endif
#endif
    size = 1U + randombytes_uniform(100000U);
    buf  = sodium_malloc(size);
    assert(buf != NULL);

/* old versions of asan emit a warning because they don't support mlock*() */
#ifndef __SANITIZE_ADDRESS__
    sodium_mprotect_readonly(buf);
    sodium_mprotect_readwrite(buf);
#endif

#if defined(HAVE_CATCHABLE_SEGV) && !defined(__EMSCRIPTEN__) && !defined(__SANITIZE_ADDRESS__)
    sodium_memzero(((unsigned char *) buf) + size, 1U);
    sodium_mprotect_noaccess(buf);
    sodium_free(buf);
    printf("Overflow not caught\n");
#else
    segv_handler(0);
#endif
    return 0;
}