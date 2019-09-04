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
struct object_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_object_request (struct object_request*) ; 

__attribute__((used)) static void abort_object_request(struct object_request *obj_req)
{
	release_object_request(obj_req);
}