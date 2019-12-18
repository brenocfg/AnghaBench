#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int initialized; scalar_t__ getentropy_available; scalar_t__ getrandom_available; int random_data_source_fd; int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {scalar_t__ nonce; size_t rnd32_outleft; int initialized; scalar_t__ key; int /*<<< orphan*/  rnd32; } ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  RtlGenRandom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc4random_buf (scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getpid () ; 
 TYPE_2__ global ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ randombytes_getentropy (scalar_t__,int) ; 
 int /*<<< orphan*/  randombytes_internal_random_init () ; 
 scalar_t__ randombytes_linux_getrandom (scalar_t__,int) ; 
 scalar_t__ safe_read (int,scalar_t__,int) ; 
 scalar_t__ sodium_hrtime () ; 
 int /*<<< orphan*/  sodium_misuse () ; 
 TYPE_1__ stream ; 

__attribute__((used)) static void
randombytes_internal_random_stir(void)
{
    stream.nonce = sodium_hrtime();
    assert(stream.nonce != (uint64_t) 0U);
    memset(stream.rnd32, 0, sizeof stream.rnd32);
    stream.rnd32_outleft = (size_t) 0U;
    if (global.initialized == 0) {
        randombytes_internal_random_init();
        global.initialized = 1;
    }
#ifdef HAVE_GETPID
    global.pid = getpid();
#endif

#ifndef _WIN32

# ifdef HAVE_GETENTROPY
     if (global.getentropy_available != 0) {
         if (randombytes_getentropy(stream.key, sizeof stream.key) != 0) {
             sodium_misuse(); /* LCOV_EXCL_LINE */
         }
     }
# elif defined(HAVE_LINUX_COMPATIBLE_GETRANDOM)
     if (global.getrandom_available != 0) {
         if (randombytes_linux_getrandom(stream.key, sizeof stream.key) != 0) {
             sodium_misuse(); /* LCOV_EXCL_LINE */
         }
     }
# elif defined(NONEXISTENT_DEV_RANDOM) && defined(HAVE_SAFE_ARC4RANDOM)
    arc4random_buf(stream.key, sizeof stream.key);
# elif !defined(NONEXISTENT_DEV_RANDOM)
    if (global.random_data_source_fd == -1 ||
        safe_read(global.random_data_source_fd, stream.key,
                  sizeof stream.key) != (ssize_t) sizeof stream.key) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
# else
    sodium_misuse();
# endif

#else /* _WIN32 */
    if (! RtlGenRandom((PVOID) stream.key, (ULONG) sizeof stream.key)) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
#endif

    stream.initialized = 1;
}