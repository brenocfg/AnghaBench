#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* mime_attr; } ;
struct TYPE_8__ {TYPE_2__ res; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_6__ {scalar_t__ priority; } ;

/* Variables and functions */
 scalar_t__ H2O_MIME_ATTRIBUTE_PRIORITY_HIGHEST ; 
 int /*<<< orphan*/  h2o_req_fill_mime_attributes (TYPE_3__*) ; 

__attribute__((used)) static int is_blocking_asset(h2o_req_t *req)
{
    if (req->res.mime_attr == NULL)
        h2o_req_fill_mime_attributes(req);
    return req->res.mime_attr->priority == H2O_MIME_ATTRIBUTE_PRIORITY_HIGHEST;
}