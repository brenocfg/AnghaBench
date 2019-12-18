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
struct object_id {unsigned char* hash; } ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int rawsz; int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* final_fn ) (unsigned char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int GIT_MAX_RAWSZ ; 
 int /*<<< orphan*/  stub1 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 

void flush_one_hunk(struct object_id *result, git_hash_ctx *ctx)
{
	unsigned char hash[GIT_MAX_RAWSZ];
	unsigned short carry = 0;
	int i;

	the_hash_algo->final_fn(hash, ctx);
	the_hash_algo->init_fn(ctx);
	/* 20-byte sum, with carry */
	for (i = 0; i < the_hash_algo->rawsz; ++i) {
		carry += result->hash[i] + hash[i];
		result->hash[i] = carry;
		carry >>= 8;
	}
}