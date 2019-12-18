#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  msg_queue; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  msg_queue_put_simple4 (int /*<<< orphan*/ *,int,int,int,void*,int) ; 

__attribute__((used)) inline static void ffp_notify_msg4(FFPlayer *ffp, int what, int arg1, int arg2, void *obj, int obj_len) {
    msg_queue_put_simple4(&ffp->msg_queue, what, arg1, arg2, obj, obj_len);
}