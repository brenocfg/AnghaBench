#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t sz; int fd; scalar_t__ data; } ;
struct TYPE_4__ {int num_queued_writes; TYPE_3__* queued_writes; } ;

/* Variables and functions */
 int PEER_LIMIT ; 
 int /*<<< orphan*/  PeerWriteData ; 
 TYPE_3__ empty_pwd ; 
 int /*<<< orphan*/  ensure_space_for (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  log_error (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  peer_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queued_writes ; 
 int /*<<< orphan*/  queued_writes_capacity ; 
 TYPE_1__ talk_data ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static inline bool
add_peer_writer(int fd, const char* msg, size_t msg_sz) {
    bool ok = false;
    peer_mutex(lock);
    if (talk_data.num_queued_writes < PEER_LIMIT) {
        ensure_space_for(&talk_data, queued_writes, PeerWriteData, talk_data.num_queued_writes + 1, queued_writes_capacity, 8, false);
        talk_data.queued_writes[talk_data.num_queued_writes] = empty_pwd;
        talk_data.queued_writes[talk_data.num_queued_writes].data = malloc(msg_sz);
        if (talk_data.queued_writes[talk_data.num_queued_writes].data) {
            memcpy(talk_data.queued_writes[talk_data.num_queued_writes].data, msg, msg_sz);
            talk_data.queued_writes[talk_data.num_queued_writes].sz = msg_sz;
            talk_data.queued_writes[talk_data.num_queued_writes++].fd = fd;
            ok = true;
        }
    } else log_error("Cannot send response to peer, too many peers");
    peer_mutex(unlock);
    return ok;
}