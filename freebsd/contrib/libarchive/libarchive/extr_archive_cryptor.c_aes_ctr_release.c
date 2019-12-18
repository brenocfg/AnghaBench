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
typedef  int /*<<< orphan*/  archive_crypto_ctx ;

/* Variables and functions */

__attribute__((used)) static int
aes_ctr_release(archive_crypto_ctx *ctx)
{
	(void)ctx; /* UNUSED */
	return 0;
}