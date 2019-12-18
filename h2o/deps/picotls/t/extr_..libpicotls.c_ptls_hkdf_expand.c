#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* final ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* update ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ ptls_hash_context_t ;
struct TYPE_16__ {size_t digest_size; } ;
typedef  TYPE_3__ ptls_hash_algorithm_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int PTLS_HASH_FINAL_MODE_FREE ; 
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* ptls_hmac_create (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

int ptls_hkdf_expand(ptls_hash_algorithm_t *algo, void *output, size_t outlen, ptls_iovec_t prk, ptls_iovec_t info)
{
    ptls_hash_context_t *hmac = NULL;
    size_t i;
    uint8_t digest[PTLS_MAX_DIGEST_SIZE];

    for (i = 0; (i * algo->digest_size) < outlen; ++i) {
        if (hmac == NULL) {
            if ((hmac = ptls_hmac_create(algo, prk.base, prk.len)) == NULL)
                return PTLS_ERROR_NO_MEMORY;
        } else {
            hmac->update(hmac, digest, algo->digest_size);
        }
        hmac->update(hmac, info.base, info.len);
        uint8_t gen = (uint8_t)(i + 1);
        hmac->update(hmac, &gen, 1);
        hmac->final(hmac, digest, 1);

        size_t off_start = i * algo->digest_size, off_end = off_start + algo->digest_size;
        if (off_end > outlen)
            off_end = outlen;
        memcpy((uint8_t *)output + off_start, digest, off_end - off_start);
    }

    if (hmac != NULL)
        hmac->final(hmac, NULL, PTLS_HASH_FINAL_MODE_FREE);

    ptls_clear_memory(digest, algo->digest_size);

    return 0;
}