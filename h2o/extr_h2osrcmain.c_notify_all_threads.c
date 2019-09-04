#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int size; } ;
struct TYPE_6__ {TYPE_2__* threads; TYPE_1__ thread_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  server_notifications; } ;

/* Variables and functions */
 TYPE_3__ conf ; 
 int /*<<< orphan*/  h2o_multithread_send_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void notify_all_threads(void)
{
    unsigned i;
    for (i = 0; i != conf.thread_map.size; ++i)
        h2o_multithread_send_message(&conf.threads[i].server_notifications, NULL);
}