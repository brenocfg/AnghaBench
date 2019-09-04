#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* str; } ;
typedef  TYPE_4__ h2o_timestamp_t ;
struct TYPE_9__ {int /*<<< orphan*/  headers; } ;
struct TYPE_12__ {TYPE_2__ res; int /*<<< orphan*/  pool; TYPE_1__* conn; } ;
typedef  TYPE_5__ h2o_req_t ;
struct TYPE_10__ {int /*<<< orphan*/  rfc1123; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_TOKEN_DATE ; 
 int /*<<< orphan*/  h2o_add_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ h2o_get_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void h2o_resp_add_date_header(h2o_req_t *req)
{
    h2o_timestamp_t ts = h2o_get_timestamp(req->conn->ctx, &req->pool);
    h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_DATE, NULL, ts.str->rfc1123, strlen(ts.str->rfc1123));
}