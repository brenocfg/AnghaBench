#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  headers; } ;
struct TYPE_6__ {int len; char* base; } ;
struct TYPE_7__ {TYPE_1__ res; TYPE_2__ method; } ;
typedef  TYPE_3__ h2o_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_TRANSFER_ENCODING ; 
 int h2o_find_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ h2o_memis (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int req_requires_content_length(h2o_req_t *req)
{
    int is_put_or_post = (req->method.len >= 1 && req->method.base[0] == 'P' &&
                          (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("POST")) ||
                           h2o_memis(req->method.base, req->method.len, H2O_STRLIT("PUT"))));

    return is_put_or_post && h2o_find_header(&req->res.headers, H2O_TOKEN_TRANSFER_ENCODING, -1) == -1;
}