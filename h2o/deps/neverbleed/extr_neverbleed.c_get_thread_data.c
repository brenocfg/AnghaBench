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
struct st_neverbleed_thread_data_t {scalar_t__ self_pid; int fd; } ;
typedef  int ssize_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  thread_key; int /*<<< orphan*/  auth_token; int /*<<< orphan*/  sun_; } ;
typedef  TYPE_1__ neverbleed_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,void*,int) ; 
 int /*<<< orphan*/  dief (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ getpid () ; 
 struct st_neverbleed_thread_data_t* malloc (int) ; 
 struct st_neverbleed_thread_data_t* pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,struct st_neverbleed_thread_data_t*) ; 
 int /*<<< orphan*/  set_cloexec (int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

struct st_neverbleed_thread_data_t *get_thread_data(neverbleed_t *nb)
{
    struct st_neverbleed_thread_data_t *thdata;
    pid_t self_pid = getpid();
    ssize_t r;

    if ((thdata = pthread_getspecific(nb->thread_key)) != NULL) {
        if (thdata->self_pid == self_pid)
            return thdata;
        /* we have been forked! */
        close(thdata->fd);
    } else {
        if ((thdata = malloc(sizeof(*thdata))) == NULL)
            dief("malloc failed");
    }

    thdata->self_pid = self_pid;
#ifdef SOCK_CLOEXEC
    if ((thdata->fd = socket(PF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0)) == -1)
        dief("socket(2) failed");
#else
    if ((thdata->fd = socket(PF_UNIX, SOCK_STREAM, 0)) == -1)
        dief("socket(2) failed");
    set_cloexec(thdata->fd);
#endif
    while (connect(thdata->fd, (void *)&nb->sun_, sizeof(nb->sun_)) != 0)
        if (errno != EINTR)
            dief("failed to connect to privsep daemon");
    while ((r = write(thdata->fd, nb->auth_token, sizeof(nb->auth_token))) == -1 && errno == EINTR)
        ;
    if (r != sizeof(nb->auth_token))
        dief("failed to send authentication token");
    pthread_setspecific(nb->thread_key, thdata);

    return thdata;
}