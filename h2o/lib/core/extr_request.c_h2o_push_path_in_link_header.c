#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  authority; int /*<<< orphan*/  scheme; } ;
struct TYPE_10__ {TYPE_2__* hostconf; int /*<<< orphan*/  authority; scalar_t__ res_is_delegated; int /*<<< orphan*/ * scheme; TYPE_3__ input; int /*<<< orphan*/  path_normalized; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_7__ {int /*<<< orphan*/  allow_cross_origin_push; } ;
struct TYPE_8__ {TYPE_1__ http2; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_push_path ; 
 int /*<<< orphan*/  h2o_extract_push_path_from_link_header (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (char const*,size_t) ; 

h2o_iovec_t h2o_push_path_in_link_header(h2o_req_t *req, const char *value, size_t value_len)
{
    h2o_iovec_t ret = h2o_iovec_init(value, value_len);

    h2o_extract_push_path_from_link_header(&req->pool, value, value_len, req->path_normalized, req->input.scheme,
                                           req->input.authority, req->res_is_delegated ? req->scheme : NULL,
                                           req->res_is_delegated ? &req->authority : NULL, do_push_path, req, &ret,
                                           req->hostconf->http2.allow_cross_origin_push);

    return ret;
}