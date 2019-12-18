#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int id; int /*<<< orphan*/ * method; } ;
typedef  TYPE_1__ SSL_COMP ;
typedef  int /*<<< orphan*/  COMP_METHOD ;

/* Variables and functions */
 scalar_t__ COMP_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_DISABLE ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ENABLE ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ NID_undef ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  SSL_F_SSL_COMP_ADD_COMPRESSION_METHOD ; 
 int /*<<< orphan*/  SSL_R_COMPRESSION_ID_NOT_WITHIN_PRIVATE_RANGE ; 
 int /*<<< orphan*/  SSL_R_DUPLICATE_COMPRESSION_ID ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_builtin_compressions () ; 
 scalar_t__ sk_SSL_COMP_find (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sk_SSL_COMP_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * ssl_comp_methods ; 

int SSL_COMP_add_compression_method(int id, COMP_METHOD *cm)
{
    SSL_COMP *comp;

    if (cm == NULL || COMP_get_type(cm) == NID_undef)
        return 1;

    /*-
     * According to draft-ietf-tls-compression-04.txt, the
     * compression number ranges should be the following:
     *
     *   0 to  63:  methods defined by the IETF
     *  64 to 192:  external party methods assigned by IANA
     * 193 to 255:  reserved for private use
     */
    if (id < 193 || id > 255) {
        SSLerr(SSL_F_SSL_COMP_ADD_COMPRESSION_METHOD,
               SSL_R_COMPRESSION_ID_NOT_WITHIN_PRIVATE_RANGE);
        return 1;
    }

    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);
    comp = OPENSSL_malloc(sizeof(*comp));
    if (comp == NULL) {
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
        SSLerr(SSL_F_SSL_COMP_ADD_COMPRESSION_METHOD, ERR_R_MALLOC_FAILURE);
        return 1;
    }

    comp->id = id;
    comp->method = cm;
    load_builtin_compressions();
    if (ssl_comp_methods && sk_SSL_COMP_find(ssl_comp_methods, comp) >= 0) {
        OPENSSL_free(comp);
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
        SSLerr(SSL_F_SSL_COMP_ADD_COMPRESSION_METHOD,
               SSL_R_DUPLICATE_COMPRESSION_ID);
        return 1;
    }
    if (ssl_comp_methods == NULL || !sk_SSL_COMP_push(ssl_comp_methods, comp)) {
        OPENSSL_free(comp);
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
        SSLerr(SSL_F_SSL_COMP_ADD_COMPRESSION_METHOD, ERR_R_MALLOC_FAILURE);
        return 1;
    }
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
    return 0;
}