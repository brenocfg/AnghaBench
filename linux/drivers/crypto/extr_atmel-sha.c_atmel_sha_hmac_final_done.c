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
struct atmel_sha_dev {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int atmel_sha_complete (struct atmel_sha_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_copy_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_sha_copy_ready_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_hmac_final_done(struct atmel_sha_dev *dd)
{
	/*
	 * req->result might not be sizeof(u32) aligned, so copy the
	 * digest into ctx->digest[] before memcpy() the data into
	 * req->result.
	 */
	atmel_sha_copy_hash(dd->req);
	atmel_sha_copy_ready_hash(dd->req);
	return atmel_sha_complete(dd, 0);
}