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
union poll_fd_info {int /*<<< orphan*/  fd; } ;
struct select_context {int /*<<< orphan*/  exceptfds; int /*<<< orphan*/  writefds; int /*<<< orphan*/  readfds; } ;

/* Variables and functions */
 int SELECT_EX ; 
 int SELECT_READ ; 
 int SELECT_WRITE ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int select_event_callback(void *context, int types, union poll_fd_info info) {
    struct select_context *c = context;
    if (types & SELECT_READ)
        bit_set(info.fd, c->readfds);
    if (types & SELECT_WRITE)
        bit_set(info.fd, c->writefds);
    if (types & SELECT_EX)
        bit_set(info.fd, c->exceptfds);
    if (!(types & (SELECT_READ | SELECT_WRITE | SELECT_EX)))
        return 0;
    return 1;
}