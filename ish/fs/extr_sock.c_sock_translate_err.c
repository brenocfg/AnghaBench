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
struct sockaddr {int dummy; } ;
struct fd {int /*<<< orphan*/  real_fd; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int _ECONNRESET ; 
 int _ENOTCONN ; 
 scalar_t__ errno ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

__attribute__((used)) static void sock_translate_err(struct fd *fd, int *err) {
    // on ios, when the device goes to sleep, all connected sockets are killed.
    // reads/writes return ENOTCONN, which I'm pretty sure is a violation of
    // posix. so instead, detect this and return ECONNRESET.
    if (*err == _ENOTCONN) {
        struct sockaddr addr;
        socklen_t len = sizeof(addr);
        if (getpeername(fd->real_fd, &addr, &len) < 0 && errno == EINVAL) {
            *err = _ECONNRESET;
        }
    }
}