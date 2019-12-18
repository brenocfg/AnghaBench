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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int,void*,size_t) ; 

__attribute__((used)) static int read_nbytes(int fd, void *p, size_t sz)
{
    while (sz != 0) {
        ssize_t r;
        while ((r = read(fd, p, sz)) == -1 && errno == EINTR)
            ;
        if (r == -1) {
            return -1;
        } else if (r == 0) {
            errno = 0;
            return -1;
        }
        p = (char *)p + r;
        sz -= r;
    }
    return 0;
}