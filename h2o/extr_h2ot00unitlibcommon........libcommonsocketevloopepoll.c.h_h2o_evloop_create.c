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
struct st_h2o_evloop_epoll_t {int /*<<< orphan*/  super; int /*<<< orphan*/  ep; } ;
typedef  int /*<<< orphan*/  h2o_evloop_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  cloexec_mutex ; 
 scalar_t__ create_evloop (int) ; 
 int /*<<< orphan*/  epoll_create (int) ; 
 scalar_t__ errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_strerror_r (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

h2o_evloop_t *h2o_evloop_create(void)
{
    struct st_h2o_evloop_epoll_t *loop = (struct st_h2o_evloop_epoll_t *)create_evloop(sizeof(*loop));

    pthread_mutex_lock(&cloexec_mutex);
    loop->ep = epoll_create(10);
    while (fcntl(loop->ep, F_SETFD, FD_CLOEXEC) == -1) {
        if (errno != EAGAIN) {
            char buf[128];
            h2o_fatal("h2o_evloop_create: failed to set FD_CLOEXEC: %s\n", h2o_strerror_r(errno, buf, sizeof(buf)));
        }
    }
    pthread_mutex_unlock(&cloexec_mutex);

    return &loop->super;
}