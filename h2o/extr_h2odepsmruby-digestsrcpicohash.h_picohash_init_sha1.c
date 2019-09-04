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
struct TYPE_3__ {int /*<<< orphan*/  _sha1; void* _final; void* _update; void* _reset; int /*<<< orphan*/  digest_length; int /*<<< orphan*/  block_length; } ;
typedef  TYPE_1__ picohash_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICOHASH_SHA1_BLOCK_LENGTH ; 
 int /*<<< orphan*/  PICOHASH_SHA1_DIGEST_LENGTH ; 
 scalar_t__ _picohash_sha1_final ; 
 int /*<<< orphan*/  _picohash_sha1_init (int /*<<< orphan*/ *) ; 
 scalar_t__ _picohash_sha1_update ; 

inline void picohash_init_sha1(picohash_ctx_t *ctx)
{
    ctx->block_length = PICOHASH_SHA1_BLOCK_LENGTH;
    ctx->digest_length = PICOHASH_SHA1_DIGEST_LENGTH;
    ctx->_reset = (void *)_picohash_sha1_init;
    ctx->_update = (void *)_picohash_sha1_update;
    ctx->_final = (void *)_picohash_sha1_final;
    _picohash_sha1_init(&ctx->_sha1);
}