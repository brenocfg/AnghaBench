#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* cert; int /*<<< orphan*/ * psk_find_session_cb; int /*<<< orphan*/ * psk_server_callback; } ;
struct TYPE_8__ {TYPE_1__* pkeys; int /*<<< orphan*/ * cert_cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  privatekey; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int EC_GROUP_get_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ ) ; 
#define  SSL_PKEY_DSA_SIGN 131 
 int SSL_PKEY_ECC ; 
#define  SSL_PKEY_GOST01 130 
#define  SSL_PKEY_GOST12_256 129 
#define  SSL_PKEY_GOST12_512 128 
 int SSL_PKEY_NUM ; 
 int /*<<< orphan*/  ssl_has_cert (TYPE_3__ const*,int) ; 
 scalar_t__ tls_check_sigalg_curve (TYPE_3__ const*,int) ; 

__attribute__((used)) static int is_tls13_capable(const SSL *s)
{
    int i;
#ifndef OPENSSL_NO_EC
    int curve;
    EC_KEY *eckey;
#endif

#ifndef OPENSSL_NO_PSK
    if (s->psk_server_callback != NULL)
        return 1;
#endif

    if (s->psk_find_session_cb != NULL || s->cert->cert_cb != NULL)
        return 1;

    for (i = 0; i < SSL_PKEY_NUM; i++) {
        /* Skip over certs disallowed for TLSv1.3 */
        switch (i) {
        case SSL_PKEY_DSA_SIGN:
        case SSL_PKEY_GOST01:
        case SSL_PKEY_GOST12_256:
        case SSL_PKEY_GOST12_512:
            continue;
        default:
            break;
        }
        if (!ssl_has_cert(s, i))
            continue;
#ifndef OPENSSL_NO_EC
        if (i != SSL_PKEY_ECC)
            return 1;
        /*
         * Prior to TLSv1.3 sig algs allowed any curve to be used. TLSv1.3 is
         * more restrictive so check that our sig algs are consistent with this
         * EC cert. See section 4.2.3 of RFC8446.
         */
        eckey = EVP_PKEY_get0_EC_KEY(s->cert->pkeys[SSL_PKEY_ECC].privatekey);
        if (eckey == NULL)
            continue;
        curve = EC_GROUP_get_curve_name(EC_KEY_get0_group(eckey));
        if (tls_check_sigalg_curve(s, curve))
            return 1;
#else
        return 1;
#endif
    }

    return 0;
}