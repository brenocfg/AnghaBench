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
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int crypto_shash_statesize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 void* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int padlock_sha_import_nano(struct shash_desc *desc,
				const void *in)
{
	int statesize = crypto_shash_statesize(desc->tfm);
	void *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, statesize);
	return 0;
}