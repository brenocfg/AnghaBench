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
struct ahash_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int __ahash_finup (struct ahash_request*) ; 
 int __ahash_init (struct ahash_request*) ; 
 int /*<<< orphan*/  flow_log (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_digest(struct ahash_request *req)
{
	int err = 0;

	flow_log("ahash_digest() nbytes:%u\n", req->nbytes);

	/* whole thing at once */
	err = __ahash_init(req);
	if (!err)
		err = __ahash_finup(req);

	return err;
}