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
struct TYPE_4__ {int what; } ;
typedef  int /*<<< orphan*/  MessageQueue ;
typedef  TYPE_1__ AVMessage ;

/* Variables and functions */
 int /*<<< orphan*/  msg_init_msg (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_queue_put (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) inline static void msg_queue_put_simple1(MessageQueue *q, int what)
{
    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = what;
    msg_queue_put(q, &msg);
}