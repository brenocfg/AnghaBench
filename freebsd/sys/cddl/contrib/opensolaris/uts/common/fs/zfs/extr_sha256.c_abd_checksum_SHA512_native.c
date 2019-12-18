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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  abd_t ;
typedef  int /*<<< orphan*/  SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_256_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha512_incremental ; 

void
abd_checksum_SHA512_native(abd_t *abd, uint64_t size,
    const void *ctx_template, zio_cksum_t *zcp)
{
	SHA512_CTX	ctx;

	SHA512_256_Init(&ctx);
	(void) abd_iterate_func(abd, 0, size, sha512_incremental, &ctx);
	SHA512_256_Final((unsigned char *)zcp, &ctx);
}