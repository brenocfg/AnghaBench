#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ h2o_req_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_PROBE_CONN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECEIVE_REQUEST_HEADER ; 

__attribute__((used)) __attribute__((noinline)) static void h2o_probe_request_header(h2o_req_t *req, uint64_t req_index, h2o_iovec_t name,
                                                               h2o_iovec_t value)
{
    H2O_PROBE_CONN(RECEIVE_REQUEST_HEADER, req->conn, req_index, name.base, name.len, value.base, value.len);
}