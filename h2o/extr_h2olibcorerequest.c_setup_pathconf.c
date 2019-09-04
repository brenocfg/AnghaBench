#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int len; char* base; } ;
struct TYPE_15__ {TYPE_2__ path_normalized; } ;
typedef  TYPE_4__ h2o_req_t ;
struct TYPE_14__ {int len; char* base; } ;
struct TYPE_16__ {TYPE_3__ path; } ;
typedef  TYPE_5__ h2o_pathconf_t ;
struct TYPE_12__ {size_t size; TYPE_5__* entries; } ;
struct TYPE_17__ {TYPE_1__ paths; TYPE_5__ fallback_path; } ;
typedef  TYPE_6__ h2o_hostconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_req_bind_conf (TYPE_4__*,TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

__attribute__((used)) static void setup_pathconf(h2o_req_t *req, h2o_hostconf_t *hostconf)
{
    h2o_pathconf_t *selected_pathconf = &hostconf->fallback_path;
    size_t i;

    /* setup pathconf, or redirect to "path/" */
    for (i = 0; i != hostconf->paths.size; ++i) {
        h2o_pathconf_t *candidate = hostconf->paths.entries + i;
        if (req->path_normalized.len >= candidate->path.len &&
            memcmp(req->path_normalized.base, candidate->path.base, candidate->path.len) == 0 &&
            (candidate->path.base[candidate->path.len - 1] == '/' || req->path_normalized.len == candidate->path.len ||
             req->path_normalized.base[candidate->path.len] == '/')) {
            selected_pathconf = candidate;
            break;
        }
    }
    h2o_req_bind_conf(req, hostconf, selected_pathconf);
}