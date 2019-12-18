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
typedef  int /*<<< orphan*/  h2o_multithread_receiver_t ;
typedef  int /*<<< orphan*/  h2o_linklist_t ;
struct TYPE_2__ {int /*<<< orphan*/  ping_receiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_empty_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_empty_message (int /*<<< orphan*/ *) ; 
 TYPE_1__ worker_thread ; 

__attribute__((used)) static void on_pong(h2o_multithread_receiver_t *receiver, h2o_linklist_t *list)
{
    while (!h2o_linklist_is_empty(list)) {
        pop_empty_message(list);
        send_empty_message(&worker_thread.ping_receiver);
    }
}