#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  len; } ;
struct TYPE_12__ {int /*<<< orphan*/  pool; TYPE_3__* pathconf; TYPE_5__ path_normalized; int /*<<< orphan*/  path; int /*<<< orphan*/  query_at; } ;
typedef  TYPE_2__ h2o_req_t ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {TYPE_1__ member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ h2o_pathconf_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_4__ h2o_build_destination (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2o_concat (int /*<<< orphan*/ *,TYPE_5__,TYPE_5__) ; 
 int /*<<< orphan*/  h2o_init_request (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__ h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 

void test_percent_encode_zero_byte(void)
{
    h2o_pathconf_t pathconf = {NULL, {H2O_STRLIT("/abc")}};
    h2o_req_t req;
    h2o_iovec_t dest;

    h2o_init_request(&req, NULL, NULL);

    /* basic pattern */
    req.path_normalized = h2o_iovec_init(H2O_STRLIT("/abc/mno\0xyz"));
    req.query_at = req.path_normalized.len;
    req.path = h2o_concat(&req.pool, req.path_normalized, h2o_iovec_init(H2O_STRLIT("?q")));
    req.pathconf = &pathconf;
    dest = h2o_build_destination(&req, H2O_STRLIT("/def"), 1);
    ok(h2o_memis(dest.base, dest.len, H2O_STRLIT("/def/mno%00xyz?q")));
    dest = h2o_build_destination(&req, H2O_STRLIT("/def/"), 1);
    ok(h2o_memis(dest.base, dest.len, H2O_STRLIT("/def/mno%00xyz?q")));

    h2o_mem_clear_pool(&req.pool);
}