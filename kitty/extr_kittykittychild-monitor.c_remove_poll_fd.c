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
struct pollfd {int fd; } ;
struct TYPE_2__ {size_t num_talk_fds; size_t num_listen_fds; struct pollfd* fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (struct pollfd*,struct pollfd*,size_t) ; 
 TYPE_1__ talk_data ; 

__attribute__((used)) static inline void
remove_poll_fd(int fd) {
    size_t count = talk_data.num_talk_fds + talk_data.num_listen_fds;
    for (size_t i = talk_data.num_listen_fds; i < count; i++) {
        struct pollfd *pfd = talk_data.fds + i;
        if (pfd->fd == fd) {
            size_t num_to_right = count - 1 - i;
            if (num_to_right) memmove(talk_data.fds + i, talk_data.fds + i + 1, num_to_right * sizeof(struct pollfd));
            talk_data.num_talk_fds--;
            break;
        }
    }
}