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
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  add_peer_writer (int,char const*,size_t) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_talk_loop (int) ; 

__attribute__((used)) static void
send_response(int fd, const char *msg, size_t msg_sz) {
    if (msg == NULL) { shutdown(fd, SHUT_WR); close(fd); return; }
    if (!add_peer_writer(fd, msg, msg_sz)) { shutdown(fd, SHUT_WR); close(fd); }
    else wakeup_talk_loop(false);
}