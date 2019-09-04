#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {size_t num_writes; TYPE_1__* writes; } ;
struct TYPE_3__ {int fd; scalar_t__ data; scalar_t__ pos; scalar_t__ sz; int finished; } ;
typedef  TYPE_1__ PeerWriteData ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_error (char*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ send (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ talk_data ; 

__attribute__((used)) static inline bool
write_to_peer(int fd) {
    bool write_finished = false;
    for (size_t i = 0; i < talk_data.num_writes; i++) {
        PeerWriteData *wd = talk_data.writes + i;
#define failed(msg) { write_finished = true; log_error("%s", msg); wd->finished = true; break; }
        if (wd->fd == fd) {
            ssize_t n = send(fd, wd->data + wd->pos, wd->sz - wd->pos, MSG_NOSIGNAL);
            if (n == 0) { failed("send() to peer failed to send any data"); }
            else if (n < 0) {
                if (errno != EINTR) { perror("write() to peer socket failed with error"); failed(""); }
            } else {
                wd->pos += n;
                if (wd->pos >= wd->sz) { write_finished = true; wd->finished = true; }
            }
            break;
        }

    }
#undef failed
    return write_finished;
}