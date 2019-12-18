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
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {scalar_t__ getentropy_available; scalar_t__ getrandom_available; int random_data_source_fd; scalar_t__ pid; scalar_t__ initialized; } ;

/* Variables and functions */
 scalar_t__ close (int) ; 
 TYPE_1__ global ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stream ; 

__attribute__((used)) static int
randombytes_internal_random_close(void)
{
    int ret = -1;

# ifdef HAVE_GETENTROPY
    if (global.getentropy_available != 0) {
        ret = 0;
    }
# elif defined(HAVE_LINUX_COMPATIBLE_GETRANDOM)
    if (global.getrandom_available != 0) {
        ret = 0;
    }
# elif !defined(NONEXISTENT_DEV_RANDOM) && defined(HAVE_SAFE_ARC4RANDOM)
    ret = 0;
# else
    if (global.random_data_source_fd != -1 &&
        close(global.random_data_source_fd) == 0) {
        global.random_data_source_fd = -1;
        global.initialized = 0;
# ifdef HAVE_GETPID
        global.pid = (pid_t) 0;
# endif
        ret = 0;
    }
# endif

    sodium_memzero(&stream, sizeof stream);

    return ret;
}