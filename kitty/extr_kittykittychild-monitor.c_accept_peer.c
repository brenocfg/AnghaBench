#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; } ;
struct TYPE_6__ {size_t num_listen_fds; size_t num_talk_fds; size_t reads_capacity; int num_reads; TYPE_4__* reads; TYPE_1__* fds; } ;
struct TYPE_5__ {int fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 size_t PEER_LIMIT ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  PeerReadData ; 
 int /*<<< orphan*/  PollFD ; 
 scalar_t__ UNLIKELY (int) ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ empty_prd ; 
 int /*<<< orphan*/  ensure_space_for (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fds ; 
 int /*<<< orphan*/  fds_capacity ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  nuke_socket (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  reads ; 
 int /*<<< orphan*/  reads_capacity ; 
 TYPE_2__ talk_data ; 

__attribute__((used)) static inline bool
accept_peer(int listen_fd, bool shutting_down) {
    int peer = accept(listen_fd, NULL, NULL);
    if (UNLIKELY(peer == -1)) {
        if (errno == EINTR) return true;
        if (!shutting_down) perror("accept() on talk socket failed!");
        return false;
    }
    size_t fd_idx = talk_data.num_listen_fds + talk_data.num_talk_fds;
    if (fd_idx < PEER_LIMIT && talk_data.reads_capacity < PEER_LIMIT) {
        ensure_space_for(&talk_data, fds, PollFD, fd_idx + 1, fds_capacity, 8, false);
        talk_data.fds[fd_idx].fd = peer; talk_data.fds[fd_idx].events = POLLIN;
        ensure_space_for(&talk_data, reads, PeerReadData, talk_data.num_reads + 1, reads_capacity, 8, false);
        talk_data.reads[talk_data.num_reads] = empty_prd; talk_data.reads[talk_data.num_reads++].fd = peer;
        talk_data.num_talk_fds++;
    } else {
        log_error("Too many peers want to talk, ignoring one.");
        nuke_socket(peer);
    }
    return true;
}