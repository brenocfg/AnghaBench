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
struct zip_kernel_ctx {int dummy; } ;
struct crypto_scomp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (struct zip_kernel_ctx*) ; 
 int /*<<< orphan*/  zip_ctx_exit (struct zip_kernel_ctx*) ; 

void zip_free_scomp_ctx(struct crypto_scomp *tfm, void *ctx)
{
	struct zip_kernel_ctx *zip_ctx = ctx;

	zip_ctx_exit(zip_ctx);
	kzfree(zip_ctx);
}