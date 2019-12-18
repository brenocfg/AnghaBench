#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int needs_key_update; int key_update_send_request; TYPE_1__* ctx; } ;
typedef  TYPE_2__ ptls_t ;
struct TYPE_4__ {int /*<<< orphan*/ * update_traffic_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int ptls_update_key(ptls_t *tls, int request_update)
{
    assert(tls->ctx->update_traffic_key == NULL);
    tls->needs_key_update = 1;
    tls->key_update_send_request = request_update;
    return 0;
}