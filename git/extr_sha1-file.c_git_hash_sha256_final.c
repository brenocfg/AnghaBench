#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sha256; } ;
typedef  TYPE_1__ git_hash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  git_SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void git_hash_sha256_final(unsigned char *hash, git_hash_ctx *ctx)
{
	git_SHA256_Final(hash, &ctx->sha256);
}