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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  archive_crypto_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  aes_ctr_encrypt_counter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aes_ctr_update(archive_crypto_ctx *ctx, const uint8_t * const in,
    size_t in_len, uint8_t * const out, size_t *out_len)
{
	(void)ctx; /* UNUSED */
	(void)in; /* UNUSED */
	(void)in_len; /* UNUSED */
	(void)out; /* UNUSED */
	(void)out_len; /* UNUSED */
	aes_ctr_encrypt_counter(ctx); /* UNUSED */ /* Fix unused function warning */
	return -1;
}