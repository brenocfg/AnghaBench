#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_16__ {size_t size; TYPE_5__* entries; } ;
struct TYPE_15__ {TYPE_1__* scheme; int /*<<< orphan*/  path; int /*<<< orphan*/  method; int /*<<< orphan*/  authority; } ;
struct TYPE_17__ {TYPE_3__ headers; TYPE_2__ input; int /*<<< orphan*/  conn; int /*<<< orphan*/  version; } ;
typedef  TYPE_4__ h2o_req_t ;
struct TYPE_18__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
typedef  TYPE_5__ h2o_header_t ;
struct TYPE_20__ {int /*<<< orphan*/  buf; } ;
struct TYPE_19__ {int /*<<< orphan*/  buf; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ H2O_CONN_IS_PROBED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H2O_PROBE_CONN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__* H2O_TOKEN_AUTHORITY ; 
 TYPE_10__* H2O_TOKEN_METHOD ; 
 TYPE_9__* H2O_TOKEN_PATH ; 
 TYPE_8__* H2O_TOKEN_SCHEME ; 
 int /*<<< orphan*/  RECEIVE_REQUEST ; 
 int /*<<< orphan*/  RECEIVE_REQUEST_HEADER ; 
 int /*<<< orphan*/  h2o_probe_request_header (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void h2o_probe_log_request(h2o_req_t *req, uint64_t req_index)
{
    H2O_PROBE_CONN(RECEIVE_REQUEST, req->conn, req_index, req->version);
    if (H2O_CONN_IS_PROBED(RECEIVE_REQUEST_HEADER, req->conn)) {
        h2o_probe_request_header(req, req_index, H2O_TOKEN_AUTHORITY->buf, req->input.authority);
        h2o_probe_request_header(req, req_index, H2O_TOKEN_METHOD->buf, req->input.method);
        h2o_probe_request_header(req, req_index, H2O_TOKEN_PATH->buf, req->input.path);
        h2o_probe_request_header(req, req_index, H2O_TOKEN_SCHEME->buf, req->input.scheme->name);
        size_t i;
        for (i = 0; i != req->headers.size; ++i) {
            h2o_header_t *h = req->headers.entries + i;
            h2o_probe_request_header(req, req_index, *h->name, h->value);
        }
    }
}