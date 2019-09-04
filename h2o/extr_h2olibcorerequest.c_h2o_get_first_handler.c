#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* pathconf; } ;
typedef  TYPE_3__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/ ** entries; } ;
struct TYPE_8__ {TYPE_1__ handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/ * h2o_req_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  setup_pathconf (TYPE_3__*,int /*<<< orphan*/ *) ; 

h2o_handler_t *h2o_get_first_handler(h2o_req_t *req)
{
    h2o_hostconf_t *hostconf = h2o_req_setup(req);
    setup_pathconf(req, hostconf);
    return req->pathconf->handlers.size != 0 ? req->pathconf->handlers.entries[0] : NULL;
}