#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* pathconf; TYPE_1__* scheme; int /*<<< orphan*/  authority; int /*<<< orphan*/ * overrides; } ;
typedef  TYPE_4__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;
struct TYPE_10__ {int /*<<< orphan*/  entries; } ;
struct TYPE_11__ {TYPE_2__ handlers; } ;
struct TYPE_9__ {int /*<<< orphan*/  default_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_handlers (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_hostconf (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o__proxy_process_request (TYPE_4__*) ; 
 int /*<<< orphan*/  setup_pathconf (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_resolved_request(h2o_req_t *req, h2o_hostconf_t **hosts)
{
    h2o_hostconf_t *hostconf;
    if (req->overrides == NULL && (hostconf = find_hostconf(hosts, req->authority, req->scheme->default_port)) != NULL) {
        setup_pathconf(req, hostconf);
        call_handlers(req, req->pathconf->handlers.entries);
        return;
    }

    /* uses the current pathconf, in other words, proxy uses the previous pathconf for building filters */
    h2o__proxy_process_request(req);
}