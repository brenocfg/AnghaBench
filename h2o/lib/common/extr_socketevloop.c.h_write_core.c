#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iovec {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int IOV_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int writev (int,struct iovec*,int) ; 

__attribute__((used)) static int write_core(int fd, h2o_iovec_t **bufs, size_t *bufcnt, size_t *first_buf_written)
{
    int iovcnt;
    ssize_t wret;

    *first_buf_written = 0;

    while (*bufcnt != 0) {
        /* write */
        iovcnt = IOV_MAX;
        if (*bufcnt < iovcnt)
            iovcnt = (int)*bufcnt;
        while ((wret = writev(fd, (struct iovec *)*bufs, iovcnt)) == -1 && errno == EINTR)
            ;
        if (wret == -1) {
            if (errno != EAGAIN)
                return -1;
            break;
        }
        /* adjust the buffer */
        while ((*bufs)->len < wret) {
            wret -= (*bufs)->len;
            ++*bufs;
            --*bufcnt;
            --iovcnt;
        }
        assert(iovcnt > 0);
        if ((*bufs)->len == wret) {
            ++*bufs;
            --*bufcnt;
            if (--iovcnt != 0)
                break;
        } else {
            *first_buf_written = wret;
            break;
        }
    }

    return 0;
}