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
struct TYPE_4__ {int /*<<< orphan*/  _timeout; int /*<<< orphan*/ * _connect_req; } ;
typedef  TYPE_1__ h2o_httpclient_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_socketpool_cancel_connect (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_client(h2o_httpclient_t *client)
{
    if (client->_connect_req != NULL) {
        h2o_socketpool_cancel_connect(client->_connect_req);
        client->_connect_req = NULL;
    }

    if (h2o_timer_is_linked(&client->_timeout))
        h2o_timer_unlink(&client->_timeout);

    free(client);
}