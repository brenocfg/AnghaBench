#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_request {int /*<<< orphan*/  oid; int /*<<< orphan*/  walker; TYPE_1__* req; } ;
struct TYPE_2__ {scalar_t__ rename; } ;

/* Variables and functions */
 scalar_t__ finish_http_object_request (TYPE_1__*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walker_say (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finish_object_request(struct object_request *obj_req)
{
	if (finish_http_object_request(obj_req->req))
		return;

	if (obj_req->req->rename == 0)
		walker_say(obj_req->walker, "got %s\n", oid_to_hex(&obj_req->oid));
}