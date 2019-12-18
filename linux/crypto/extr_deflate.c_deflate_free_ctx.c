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
struct crypto_scomp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __deflate_exit (void*) ; 
 int /*<<< orphan*/  kzfree (void*) ; 

__attribute__((used)) static void deflate_free_ctx(struct crypto_scomp *tfm, void *ctx)
{
	__deflate_exit(ctx);
	kzfree(ctx);
}