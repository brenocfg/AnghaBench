#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_9__ {TYPE_2__* entries; } ;
struct TYPE_8__ {TYPE_5__ headers; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_USER_AGENT ; 
 scalar_t__ SIZE_MAX ; 
 int h2o_find_header (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ h2o_strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_msie(h2o_req_t *req)
{
    ssize_t cursor = h2o_find_header(&req->headers, H2O_TOKEN_USER_AGENT, -1);
    if (cursor == -1)
        return 0;
    if (h2o_strstr(req->headers.entries[cursor].value.base, req->headers.entries[cursor].value.len, H2O_STRLIT("; MSIE ")) ==
        SIZE_MAX)
        return 0;
    return 1;
}