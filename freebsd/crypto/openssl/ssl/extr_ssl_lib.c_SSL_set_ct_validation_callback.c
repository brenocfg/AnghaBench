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
typedef  int /*<<< orphan*/ * ssl_ct_validation_cb ;
struct TYPE_4__ {void* ct_validation_callback_arg; int /*<<< orphan*/ * ct_validation_callback; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 scalar_t__ SSL_CTX_has_client_custom_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_CT_VALIDATION_CALLBACK ; 
 int /*<<< orphan*/  SSL_R_CUSTOM_EXT_HANDLER_ALREADY_INSTALLED ; 
 int /*<<< orphan*/  SSL_set_tlsext_status_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_STATUSTYPE_ocsp ; 
 int /*<<< orphan*/  TLSEXT_TYPE_signed_certificate_timestamp ; 

int SSL_set_ct_validation_callback(SSL *s, ssl_ct_validation_cb callback,
                                   void *arg)
{
    /*
     * Since code exists that uses the custom extension handler for CT, look
     * for this and throw an error if they have already registered to use CT.
     */
    if (callback != NULL && SSL_CTX_has_client_custom_ext(s->ctx,
                                                          TLSEXT_TYPE_signed_certificate_timestamp))
    {
        SSLerr(SSL_F_SSL_SET_CT_VALIDATION_CALLBACK,
               SSL_R_CUSTOM_EXT_HANDLER_ALREADY_INSTALLED);
        return 0;
    }

    if (callback != NULL) {
        /*
         * If we are validating CT, then we MUST accept SCTs served via OCSP
         */
        if (!SSL_set_tlsext_status_type(s, TLSEXT_STATUSTYPE_ocsp))
            return 0;
    }

    s->ct_validation_callback = callback;
    s->ct_validation_callback_arg = arg;

    return 1;
}