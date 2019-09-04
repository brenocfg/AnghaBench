#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ h2o_timer_t ;
typedef  int /*<<< orphan*/  h2o_timer_cb ;
struct TYPE_7__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_2__ h2o_redis_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void invoke_deferred(h2o_redis_client_t *client, uint64_t tick, h2o_timer_t *entry, h2o_timer_cb cb)
{
    entry->cb = cb;
    h2o_timer_link(client->loop, tick, entry);
}