#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; TYPE_6__* entries; } ;
struct TYPE_11__ {TYPE_1__ headers; int /*<<< orphan*/  reason; } ;
struct TYPE_12__ {TYPE_4__ res; } ;
typedef  TYPE_5__ h2o_req_t ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_13__ {TYPE_3__ value; TYPE_2__* name; } ;
typedef  TYPE_6__ h2o_header_t ;
struct TYPE_9__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  H2O_UINT64_LONGEST_STR ;

/* Variables and functions */
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t flatten_headers_estimate_size(h2o_req_t *req, size_t server_name_and_connection_len)
{
    size_t len = sizeof("HTTP/1.1  \r\nserver: \r\nconnection: \r\ncontent-length: \r\n\r\n") + 3 + strlen(req->res.reason) +
                 server_name_and_connection_len + sizeof(H2O_UINT64_LONGEST_STR) - 1 + sizeof("cache-control: private") - 1;
    const h2o_header_t *header, *end;

    for (header = req->res.headers.entries, end = header + req->res.headers.size; header != end; ++header)
        len += header->name->len + header->value.len + 4;

    return len;
}