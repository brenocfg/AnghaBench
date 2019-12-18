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
struct sun4i_req_ctx {int /*<<< orphan*/  flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_HASH_FINAL ; 
 struct sun4i_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int sun4i_hash (struct ahash_request*) ; 

int sun4i_hash_final(struct ahash_request *areq)
{
	struct sun4i_req_ctx *op = ahash_request_ctx(areq);

	op->flags = SS_HASH_FINAL;
	return sun4i_hash(areq);
}