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
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SYS_getrandom ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int getrandom (void* const,size_t const,int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,void* const,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_randombytes_linux_getrandom(void * const buf, const size_t size)
{
    int readnb;

    assert(size <= 256U);
    do {
#  ifdef __dietlibc__
        readnb = getrandom(buf, size, 0);
#  else
        readnb = syscall(SYS_getrandom, buf, (int) size, 0);
#  endif
    } while (readnb < 0 && (errno == EINTR || errno == EAGAIN));

    return (readnb == (int) size) - 1;
}