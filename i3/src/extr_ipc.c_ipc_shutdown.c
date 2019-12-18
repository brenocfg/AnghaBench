#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shutdown_reason_t ;
struct TYPE_4__ {int fd; } ;
typedef  TYPE_1__ ipc_client ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  all_clients ; 
 int /*<<< orphan*/  free_ipc_client (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ipc_send_shutdown_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

void ipc_shutdown(shutdown_reason_t reason, int exempt_fd) {
    ipc_send_shutdown_event(reason);

    ipc_client *current;
    while (!TAILQ_EMPTY(&all_clients)) {
        current = TAILQ_FIRST(&all_clients);
        if (current->fd != exempt_fd) {
            shutdown(current->fd, SHUT_RDWR);
        }
        free_ipc_client(current, exempt_fd);
    }
}