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
typedef  int /*<<< orphan*/  ptls_ffx_context_t ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;
typedef  int /*<<< orphan*/  ptls_cipher_algorithm_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ptls_ffx_setup_crypto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,size_t,void const*) ; 

ptls_cipher_context_t *ptls_ffx_new(ptls_cipher_algorithm_t *algo, int is_enc, int nb_rounds, size_t bit_length, const void *key)
{
    ptls_cipher_context_t *ctx = (ptls_cipher_context_t *)malloc(sizeof(ptls_ffx_context_t));

    if (ctx != NULL) {
        memset(ctx, 0, sizeof(ptls_ffx_context_t));
        if (ptls_ffx_setup_crypto(ctx, algo, is_enc, nb_rounds, bit_length, key) != 0) {
            free(ctx);
            ctx = NULL;
        }
    }

    return ctx;
}