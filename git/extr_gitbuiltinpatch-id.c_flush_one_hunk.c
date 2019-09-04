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
struct object_id {unsigned char* hash; } ;
typedef  int /*<<< orphan*/  git_SHA_CTX ;

/* Variables and functions */
 int GIT_MAX_RAWSZ ; 
 int GIT_SHA1_RAWSZ ; 
 int /*<<< orphan*/  git_SHA1_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_SHA1_Init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_one_hunk(struct object_id *result, git_SHA_CTX *ctx)
{
	unsigned char hash[GIT_MAX_RAWSZ];
	unsigned short carry = 0;
	int i;

	git_SHA1_Final(hash, ctx);
	git_SHA1_Init(ctx);
	/* 20-byte sum, with carry */
	for (i = 0; i < GIT_SHA1_RAWSZ; ++i) {
		carry += result->hash[i] + hash[i];
		result->hash[i] = carry;
		carry >>= 8;
	}
}