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
struct TYPE_2__ {int random_data_source_fd; scalar_t__ initialized; scalar_t__ getrandom_available; } ;

/* Variables and functions */
 scalar_t__ close (int) ; 
 TYPE_1__ stream ; 

__attribute__((used)) static int
randombytes_sysrandom_close(void)
{
    int ret = -1;

# ifndef _WIN32
    if (stream.random_data_source_fd != -1 &&
        close(stream.random_data_source_fd) == 0) {
        stream.random_data_source_fd = -1;
        stream.initialized = 0;
        ret = 0;
    }
#  ifdef HAVE_LINUX_COMPATIBLE_GETRANDOM
    if (stream.getrandom_available != 0) {
        ret = 0;
    }
#  endif
# else /* _WIN32 */
    if (stream.initialized != 0) {
        stream.initialized = 0;
        ret = 0;
    }
# endif /* _WIN32 */
    return ret;
}