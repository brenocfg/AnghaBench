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
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  SIGINFO_NIL ; 
 int /*<<< orphan*/  SIGPIPE_ ; 
 int /*<<< orphan*/  current ; 
 int err_map (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  send_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int errno_map() {
    if (errno == EPIPE)
        send_signal(current, SIGPIPE_, SIGINFO_NIL);
    return err_map(errno);
}