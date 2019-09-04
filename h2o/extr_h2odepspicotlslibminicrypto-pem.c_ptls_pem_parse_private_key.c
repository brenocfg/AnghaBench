#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,char*,int) ;} ;
typedef  TYPE_1__ ptls_minicrypto_log_ctx_t ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_9__ {TYPE_7__ vec; } ;
typedef  TYPE_2__ ptls_asn1_pkcs8_private_key_t ;

/* Variables and functions */
 int PTLS_ERROR_PEM_LABEL_NOT_FOUND ; 
 int ptls_load_pem_objects (char const*,char*,TYPE_7__*,int,size_t*) ; 
 int /*<<< orphan*/  ptls_minicrypto_asn1_decode_private_key (TYPE_2__*,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ptls_pem_parse_private_key(char const *pem_fname, ptls_asn1_pkcs8_private_key_t *pkey,
                                      ptls_minicrypto_log_ctx_t *log_ctx)
{
    size_t nb_keys = 0;
    int ret = ptls_load_pem_objects(pem_fname, "PRIVATE KEY", &pkey->vec, 1, &nb_keys);

    if (ret == 0) {
        if (nb_keys != 1) {
            ret = PTLS_ERROR_PEM_LABEL_NOT_FOUND;
        }
    }

    if (ret == 0 && nb_keys == 1) {
        int decode_error = 0;

        if (log_ctx != NULL) {
            log_ctx->fn(log_ctx->ctx, "\nFound PRIVATE KEY, length = %d bytes\n", (int)pkey->vec.len);
        }

        (void)ptls_minicrypto_asn1_decode_private_key(pkey, &decode_error, log_ctx);

        if (decode_error != 0) {
            ret = decode_error;
        }
    }

    return ret;
}