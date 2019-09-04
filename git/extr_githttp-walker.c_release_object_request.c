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
struct object_request {int /*<<< orphan*/  node; TYPE_1__* req; } ;
struct TYPE_2__ {int localfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  free (struct object_request*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_object_request(struct object_request *obj_req)
{
	if (obj_req->req !=NULL && obj_req->req->localfile != -1)
		error("fd leakage in release: %d", obj_req->req->localfile);

	list_del(&obj_req->node);
	free(obj_req);
}