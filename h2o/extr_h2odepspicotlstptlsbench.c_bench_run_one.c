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
typedef  int /*<<< orphan*/  v_enc ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
typedef  int /*<<< orphan*/  h ;

/* Variables and functions */
 int BENCH_BATCH ; 
 int PTLS_ALERT_DECRYPT_ERROR ; 
 int PTLS_ERROR_NO_MEMORY ; 
 size_t PTLS_MAX_DIGEST_SIZE ; 
 scalar_t__ bench_time () ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 size_t ptls_aead_decrypt (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,size_t,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ ptls_aead_encrypt_final (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ptls_aead_encrypt_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int) ; 
 size_t ptls_aead_encrypt_update (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,size_t) ; 

__attribute__((used)) static int bench_run_one(ptls_aead_context_t *e, ptls_aead_context_t *d, size_t n, size_t l, uint64_t *t_enc, uint64_t *t_dec,
                     uint64_t *s)
{
    int ret = 0;
    uint8_t *v_in = NULL;
    uint8_t *v_enc[BENCH_BATCH];
    uint8_t *v_dec = NULL;
    uint64_t h[4];

    *t_enc = 0;
    *t_dec = 0;
    *s = 0;

    memset(v_enc, 0, sizeof(v_enc));
    memset(h, 0, sizeof(h));
    v_in = (uint8_t *)malloc(l);
    v_dec = (uint8_t *)malloc(l);
    if (v_in == NULL || v_dec == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
    }

    for (size_t i = 0; ret == 0 && i < BENCH_BATCH; i++) {
        v_enc[i] = (uint8_t *)malloc(l + PTLS_MAX_DIGEST_SIZE);
        if (v_enc[i] == 0) {
            ret = PTLS_ERROR_NO_MEMORY;
        }
    }

    if (ret == 0) {
        memset(v_in, 0, l);

        for (size_t k = 0; k < n;) {
            size_t e_len;
            size_t d_len;
            size_t i_max = ((n - k) > BENCH_BATCH) ? BENCH_BATCH : n - k;
            uint64_t old_h = h[0];
            uint64_t t_start = bench_time();
            uint64_t t_medium;
            uint64_t t_end;

            for (size_t i = 0; i < i_max; i++) {
                h[0]++;

                ptls_aead_encrypt_init(e, h[0], h, sizeof(h));
                e_len = ptls_aead_encrypt_update(e, v_enc[i], v_in, l);
                e_len += ptls_aead_encrypt_final(e, v_enc[i] + e_len);

                *s += (v_enc[i])[l];
            }

            t_medium = bench_time();

            h[0] = old_h;

            for (size_t i = 0; i < i_max; i++) {
                h[0]++;

                d_len = ptls_aead_decrypt(d, v_dec, v_enc[i], e_len, h[0], h, sizeof(h));
                if (d_len != l) {
                    ret = PTLS_ALERT_DECRYPT_ERROR;
                    break;
                }
                *s += v_dec[0];
            }

            t_end = bench_time();

            *t_enc += t_medium - t_start;
            *t_dec += t_end - t_medium;

            k += i_max;
        }
    }

    if (v_in != NULL) {
        free(v_in);
    }

    for (size_t i = 0; i < BENCH_BATCH; i++) {
        if (v_enc[i] != NULL) {
            free(v_enc[i]);
        }
    }

    if (v_dec != NULL) {
        free(v_dec);
    }

    return ret;
}