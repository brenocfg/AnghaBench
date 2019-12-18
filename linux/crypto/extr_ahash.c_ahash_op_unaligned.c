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
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  ahash_op_unaligned_done ; 
 int /*<<< orphan*/  ahash_restore_req (struct ahash_request*,int) ; 
 int ahash_save_req (struct ahash_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_op_unaligned(struct ahash_request *req,
			      int (*op)(struct ahash_request *))
{
	int err;

	err = ahash_save_req(req, ahash_op_unaligned_done);
	if (err)
		return err;

	err = op(req);
	if (err == -EINPROGRESS || err == -EBUSY)
		return err;

	ahash_restore_req(req, err);

	return err;
}