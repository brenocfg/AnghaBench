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
typedef  int /*<<< orphan*/  _picohash_sha256_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICOHASH_SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  _picohash_sha256_do_final (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

inline void _picohash_sha256_final(_picohash_sha256_ctx_t *ctx, void *digest)
{
    _picohash_sha256_do_final(ctx, digest, PICOHASH_SHA256_DIGEST_LENGTH);
}