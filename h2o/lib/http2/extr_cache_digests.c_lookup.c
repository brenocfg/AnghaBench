#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {scalar_t__ size; TYPE_3__* entries; } ;
typedef  TYPE_2__ h2o_cache_digests_frame_vector_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * entries; } ;
struct TYPE_7__ {int capacity_bits; TYPE_1__ keys; } ;
typedef  TYPE_3__ h2o_cache_digests_frame_t ;

/* Variables and functions */
 int H2O_CACHE_DIGESTS_STATE_FRESH ; 
 int H2O_CACHE_DIGESTS_STATE_NOT_CACHED ; 
 int H2O_CACHE_DIGESTS_STATE_STALE ; 
 int H2O_CACHE_DIGESTS_STATE_UNKNOWN ; 
 int /*<<< orphan*/ * bsearch (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int calc_hash (char const*,size_t,char const*,size_t) ; 
 int /*<<< orphan*/  cmp_key ; 

__attribute__((used)) static int lookup(h2o_cache_digests_frame_vector_t *vector, const char *url, size_t url_len, const char *etag, size_t etag_len,
                  int is_fresh, int is_complete)
{
    if (vector->size != 0) {
        uint64_t hash = calc_hash(url, url_len, etag, etag_len);
        size_t i = 0;
        do {
            h2o_cache_digests_frame_t *frame = vector->entries + i;
            uint64_t key = hash >> (64 - frame->capacity_bits);
            if (frame->keys.entries != NULL &&
                bsearch(&key, frame->keys.entries, frame->keys.size, sizeof(frame->keys.entries[0]), cmp_key) != NULL)
                return is_fresh ? H2O_CACHE_DIGESTS_STATE_FRESH : H2O_CACHE_DIGESTS_STATE_STALE;
        } while (++i != vector->size);
    }

    return is_complete ? H2O_CACHE_DIGESTS_STATE_NOT_CACHED : H2O_CACHE_DIGESTS_STATE_UNKNOWN;
}