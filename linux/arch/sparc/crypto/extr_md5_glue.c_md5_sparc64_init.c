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
struct shash_desc {int dummy; } ;
struct md5_state {scalar_t__ byte_count; void** hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_H0 ; 
 int /*<<< orphan*/  MD5_H1 ; 
 int /*<<< orphan*/  MD5_H2 ; 
 int /*<<< orphan*/  MD5_H3 ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct md5_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int md5_sparc64_init(struct shash_desc *desc)
{
	struct md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = cpu_to_le32(MD5_H0);
	mctx->hash[1] = cpu_to_le32(MD5_H1);
	mctx->hash[2] = cpu_to_le32(MD5_H2);
	mctx->hash[3] = cpu_to_le32(MD5_H3);
	mctx->byte_count = 0;

	return 0;
}