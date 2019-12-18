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
struct TYPE_3__ {int /*<<< orphan*/ * obj; int /*<<< orphan*/  (* free_l ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ AVMessage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static void msg_free_res(AVMessage *msg)
{
    if (!msg || !msg->obj)
        return;
    assert(msg->free_l);
    msg->free_l(msg->obj);
    msg->obj = NULL;
}