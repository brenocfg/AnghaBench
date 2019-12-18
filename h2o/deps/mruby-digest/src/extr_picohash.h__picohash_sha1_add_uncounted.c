#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {size_t bufferOffset; scalar_t__ buffer; } ;
typedef  TYPE_1__ _picohash_sha1_ctx_t ;

/* Variables and functions */
 int PICOHASH_SHA1_BLOCK_LENGTH ; 
 int /*<<< orphan*/  _picohash_sha1_hash_block (TYPE_1__*) ; 

__attribute__((used)) static inline void _picohash_sha1_add_uncounted(_picohash_sha1_ctx_t *s, uint8_t data)
{
    uint8_t *const b = (uint8_t *)s->buffer;
#ifdef _PICOHASH_BIG_ENDIAN
    b[s->bufferOffset] = data;
#else
    b[s->bufferOffset ^ 3] = data;
#endif
    s->bufferOffset++;
    if (s->bufferOffset == PICOHASH_SHA1_BLOCK_LENGTH) {
        _picohash_sha1_hash_block(s);
        s->bufferOffset = 0;
    }
}