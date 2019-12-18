#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {scalar_t__ getrandom_available; int random_data_source_fd; } ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  RtlGenRandom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t const ULONG_LONG_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int randombytes_BYTES_MAX ; 
 scalar_t__ randombytes_linux_getrandom (void* const,size_t const) ; 
 int /*<<< orphan*/  randombytes_sysrandom_stir_if_needed () ; 
 scalar_t__ safe_read (int,void* const,size_t const) ; 
 int /*<<< orphan*/  sodium_misuse () ; 
 TYPE_1__ stream ; 

__attribute__((used)) static void
randombytes_sysrandom_buf(void * const buf, const size_t size)
{
    randombytes_sysrandom_stir_if_needed();
#if defined(ULONG_LONG_MAX) && defined(SIZE_MAX)
# if SIZE_MAX > ULONG_LONG_MAX
    /* coverity[result_independent_of_operands] */
    assert(size <= ULONG_LONG_MAX);
# endif
#endif
#ifndef _WIN32
# if defined(SYS_getrandom) && defined(__NR_getrandom)
    if (stream.getrandom_available != 0) {
        if (randombytes_linux_getrandom(buf, size) != 0) {
            sodium_misuse(); /* LCOV_EXCL_LINE */
        }
        return;
    }
# endif
    if (stream.random_data_source_fd == -1 ||
        safe_read(stream.random_data_source_fd, buf, size) != (ssize_t) size) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
#else
    COMPILER_ASSERT(randombytes_BYTES_MAX <= 0xffffffffUL);
    if (size > (size_t) 0xffffffffUL) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
    if (! RtlGenRandom((PVOID) buf, (ULONG) size)) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
#endif
}