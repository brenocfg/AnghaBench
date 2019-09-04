#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_1__ method; } ;
struct TYPE_8__ {scalar_t__ content_length; int status; } ;
struct TYPE_9__ {int version; TYPE_2__ input; TYPE_3__ res; } ;
typedef  TYPE_4__ h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 scalar_t__ SIZE_MAX ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int should_use_chunked_encoding(h2o_req_t *req)
{
    if (req->version != 0x101)
        return 0;
    /* do nothing if content-length is known */
    if (req->res.content_length != SIZE_MAX)
        return 0;
    /* RFC 2616 4.4 states that the following status codes (and response to a HEAD method) should not include message body */
    if ((100 <= req->res.status && req->res.status <= 199) || req->res.status == 204 || req->res.status == 304)
        return 0;
    if (h2o_memis(req->input.method.base, req->input.method.len, H2O_STRLIT("HEAD")))
        return 0;

    return 1;
}