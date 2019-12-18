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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
#define  SSL_CT_VALIDATION_PERMISSIVE 129 
#define  SSL_CT_VALIDATION_STRICT 128 
 int /*<<< orphan*/  SSL_F_SSL_ENABLE_CT ; 
 int /*<<< orphan*/  SSL_R_INVALID_CT_VALIDATION_TYPE ; 
 int SSL_set_ct_validation_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_permissive ; 
 int /*<<< orphan*/  ct_strict ; 

int SSL_enable_ct(SSL *s, int validation_mode)
{
    switch (validation_mode) {
    default:
        SSLerr(SSL_F_SSL_ENABLE_CT, SSL_R_INVALID_CT_VALIDATION_TYPE);
        return 0;
    case SSL_CT_VALIDATION_PERMISSIVE:
        return SSL_set_ct_validation_callback(s, ct_permissive, NULL);
    case SSL_CT_VALIDATION_STRICT:
        return SSL_set_ct_validation_callback(s, ct_strict, NULL);
    }
}