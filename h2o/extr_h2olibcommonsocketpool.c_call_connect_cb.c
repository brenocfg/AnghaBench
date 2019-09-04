#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ h2o_socketpool_target_t ;
struct TYPE_12__ {TYPE_5__* tried; } ;
struct TYPE_14__ {size_t selected_target; TYPE_3__ lb; TYPE_2__* pool; void* data; TYPE_6__* sock; int /*<<< orphan*/  (* cb ) (TYPE_6__*,char const*,void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_5__ h2o_socketpool_connect_request_t ;
typedef  int /*<<< orphan*/  (* h2o_socketpool_connect_cb ) (TYPE_6__*,char const*,void*,int /*<<< orphan*/ *) ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_6__ h2o_socket_t ;
struct TYPE_10__ {TYPE_4__** entries; } ;
struct TYPE_11__ {TYPE_1__ targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_5__*) ; 

__attribute__((used)) static void call_connect_cb(h2o_socketpool_connect_request_t *req, const char *errstr)
{
    h2o_socketpool_connect_cb cb = req->cb;
    h2o_socket_t *sock = req->sock;
    void *data = req->data;
    h2o_socketpool_target_t *selected_target = req->pool->targets.entries[req->selected_target];

    if (req->lb.tried != NULL) {
        free(req->lb.tried);
    }

    free(req);

    if (sock != NULL)
        sock->data = NULL;
    cb(sock, errstr, data, &selected_target->url);
}