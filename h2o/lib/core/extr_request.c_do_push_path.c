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
struct TYPE_7__ {TYPE_2__* conn; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_6__ {TYPE_1__* callbacks; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* push_path ) (TYPE_3__*,char const*,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,char const*,size_t,int) ; 

__attribute__((used)) static void do_push_path(void *_req, const char *path, size_t path_len, int is_critical)
{
    h2o_req_t *req = _req;

    if (req->conn->callbacks->push_path != NULL)
        req->conn->callbacks->push_path(req, path, path_len, is_critical);
}