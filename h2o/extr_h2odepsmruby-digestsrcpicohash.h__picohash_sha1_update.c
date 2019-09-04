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
struct TYPE_4__ {int /*<<< orphan*/  byteCount; } ;
typedef  TYPE_1__ _picohash_sha1_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  _picohash_sha1_add_uncounted (TYPE_1__*,int /*<<< orphan*/ ) ; 

inline void _picohash_sha1_update(_picohash_sha1_ctx_t *s, const void *_data, size_t len)
{
    const uint8_t *data = _data;
    for (; len != 0; --len) {
        ++s->byteCount;
        _picohash_sha1_add_uncounted(s, *data++);
    }
}