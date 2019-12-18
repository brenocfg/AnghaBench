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
typedef  int /*<<< orphan*/  u_int8_t ;
struct chacha_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int /*<<< orphan*/  explicit_bzero (struct chacha_ctx*,int) ; 
 int /*<<< orphan*/  free (struct chacha_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chacha20_xform_zerokey(u_int8_t **sched)
{
	struct chacha_ctx *ctx;

	ctx = (void *)*sched;
	explicit_bzero(ctx, sizeof(*ctx));
	free(ctx, M_CRYPTO_DATA);
	*sched = NULL;
}