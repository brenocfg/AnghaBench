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
struct gctl_req {int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 int /*<<< orphan*/  gctl_set_error (struct gctl_req*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nomemmsg ; 

__attribute__((used)) static void
gctl_check_alloc(struct gctl_req *req, void *ptr)
{

	if (ptr != NULL)
		return;
	gctl_set_error(req, nomemmsg);
	if (req->error == NULL)
		req->error = nomemmsg;
}