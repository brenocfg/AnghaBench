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
struct ib_uverbs_file {int dummy; } ;
struct ib_uverbs_ex_create_cq_resp {int /*<<< orphan*/  response_length; } ;
struct ib_udata {int dummy; } ;
struct ib_ucq_object {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct ib_uverbs_ex_create_cq_resp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ib_uverbs_ex_create_cq_cb(struct ib_uverbs_file *file,
				     struct ib_ucq_object *obj,
				     struct ib_uverbs_ex_create_cq_resp *resp,
				     struct ib_udata *ucore, void *context)
{
	if (ib_copy_to_udata(ucore, resp, resp->response_length))
		return -EFAULT;

	return 0;
}