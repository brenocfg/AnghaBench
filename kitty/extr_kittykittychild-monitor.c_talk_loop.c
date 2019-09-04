#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fd; int events; int revents; } ;
struct TYPE_8__ {int* wakeup_fds; size_t num_listen_fds; size_t num_talk_fds; TYPE_4__* queued_writes; TYPE_4__* writes; TYPE_4__* reads; TYPE_4__* fds; scalar_t__ num_queued_writes; int /*<<< orphan*/  peer_lock; } ;
struct TYPE_7__ {int talk_fd; int listen_fd; int /*<<< orphan*/  shutting_down; } ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ LIKELY (int) ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  PollFD ; 
 int /*<<< orphan*/  accept_peer (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  drain_fd (int) ; 
 int /*<<< orphan*/  ensure_space_for (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fds ; 
 int /*<<< orphan*/  fds_capacity ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  move_queued_writes () ; 
 int /*<<< orphan*/  peer_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (TYPE_4__*,size_t,int) ; 
 int /*<<< orphan*/  prune_finished_reads () ; 
 int /*<<< orphan*/  prune_finished_writes () ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read_from_peer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  self_pipe (int*) ; 
 int /*<<< orphan*/  set_thread_name (char*) ; 
 TYPE_2__ talk_data ; 
 int /*<<< orphan*/  unlock ; 
 scalar_t__ write_to_peer (int) ; 

__attribute__((used)) static void*
talk_loop(void *data) {
    // The talk thread loop

    ChildMonitor *self = (ChildMonitor*)data;
    set_thread_name("KittyPeerMon");
    if ((pthread_mutex_init(&talk_data.peer_lock, NULL)) != 0) { perror("Failed to create peer mutex"); return 0; }
    if (!self_pipe(talk_data.wakeup_fds)) { perror("Failed to create wakeup fds for talk thread"); return 0; }
    ensure_space_for(&talk_data, fds, PollFD, 8, fds_capacity, 8, false);
#define add_listener(which) \
    if (self->which > -1) { \
        talk_data.fds[talk_data.num_listen_fds].fd = self->which; talk_data.fds[talk_data.num_listen_fds++].events = POLLIN; \
    }
    add_listener(talk_fd); add_listener(listen_fd);
#undef add_listener
    talk_data.fds[talk_data.num_listen_fds].fd = talk_data.wakeup_fds[0]; talk_data.fds[talk_data.num_listen_fds++].events = POLLIN;

    while (LIKELY(!self->shutting_down)) {
        for (size_t i = 0; i < talk_data.num_listen_fds + talk_data.num_talk_fds; i++) { talk_data.fds[i].revents = 0; }
        int ret = poll(talk_data.fds, talk_data.num_listen_fds + talk_data.num_talk_fds, -1);
        if (ret > 0) {
            bool has_finished_reads = false, has_finished_writes = false;
            for (size_t i = 0; i < talk_data.num_listen_fds - 1; i++) {
                if (talk_data.fds[i].revents & POLLIN) {if (!accept_peer(talk_data.fds[i].fd, self->shutting_down)) goto end; }
            }
            if (talk_data.fds[talk_data.num_listen_fds - 1].revents & POLLIN) drain_fd(talk_data.fds[talk_data.num_listen_fds - 1].fd);  // wakeup
            for (size_t i = talk_data.num_listen_fds; i < talk_data.num_talk_fds + talk_data.num_listen_fds; i++) {
                if (talk_data.fds[i].revents & (POLLIN | POLLHUP)) { if (read_from_peer(self, talk_data.fds[i].fd)) has_finished_reads = true; }
                if (talk_data.fds[i].revents & POLLOUT) { if (write_to_peer(talk_data.fds[i].fd)) has_finished_writes = true; }
            }
            if (has_finished_reads) prune_finished_reads();
            if (has_finished_writes) prune_finished_writes();
            peer_mutex(lock);
            if (talk_data.num_queued_writes) move_queued_writes();
            peer_mutex(unlock);
        } else if (ret < 0) { if (errno != EAGAIN && errno != EINTR) perror("poll() on talk fds failed"); }
    }
end:
    close(talk_data.wakeup_fds[0]); close(talk_data.wakeup_fds[1]);
    free(talk_data.fds); free(talk_data.reads); free(talk_data.writes); free(talk_data.queued_writes);
    return 0;
}