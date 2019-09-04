#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* on_body ) (TYPE_2__*,char const*) ;} ;
struct TYPE_4__ {TYPE_1__ _cb; } ;
struct st_h2o_http1client_t {TYPE_2__ super; scalar_t__ _do_keepalive; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_client (struct st_h2o_http1client_t*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*) ; 

__attribute__((used)) static void on_body_error(struct st_h2o_http1client_t *client, const char *errstr)
{
    client->_do_keepalive = 0;
    client->super._cb.on_body(&client->super, errstr);
    close_client(client);
}