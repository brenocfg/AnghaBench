#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct http_req {scalar_t__ body_size; int /*<<< orphan*/ * body; scalar_t__ num_headers; int /*<<< orphan*/ * headers; int /*<<< orphan*/ * response; } ;

/* Variables and functions */

__attribute__((used)) static void
http_req_zero(struct http_req *req)
{
    req->response = NULL;
    req->headers = NULL;
    req->num_headers = 0;
    req->body = NULL;
    req->body_size = 0;
}