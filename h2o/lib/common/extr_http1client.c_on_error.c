#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* on_body ) (TYPE_3__*,char const*) ;int /*<<< orphan*/  (* on_head ) (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__ _cb; } ;
struct TYPE_7__ {int res; } ;
struct st_h2o_http1client_t {TYPE_3__ super; int /*<<< orphan*/  (* proceed_req ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__ state; scalar_t__ _do_keepalive; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_ERROR ; 
#define  STREAM_STATE_BODY 130 
#define  STREAM_STATE_CLOSED 129 
#define  STREAM_STATE_HEAD 128 
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_error(struct st_h2o_http1client_t *client, const char *errstr)
{
    client->_do_keepalive = 0;
    switch (client->state.res) {
    case STREAM_STATE_HEAD:
        client->super._cb.on_head(&client->super, errstr, 0, 0, h2o_iovec_init(NULL, 0), NULL, 0, 0);
        break;
    case STREAM_STATE_BODY:
        client->super._cb.on_body(&client->super, errstr);
        break;
    case STREAM_STATE_CLOSED:
        if (client->proceed_req != NULL) {
            client->proceed_req(&client->super, 0, H2O_SEND_STATE_ERROR);
        }
        break;
    }
    close_client(client);
}