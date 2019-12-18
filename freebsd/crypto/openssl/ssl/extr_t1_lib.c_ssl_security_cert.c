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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_R_CA_KEY_TOO_SMALL ; 
 int SSL_R_CA_MD_TOO_WEAK ; 
 int SSL_R_EE_KEY_TOO_SMALL ; 
 int SSL_SECOP_CA_KEY ; 
 int SSL_SECOP_CA_MD ; 
 int SSL_SECOP_EE_KEY ; 
 int SSL_SECOP_PEER ; 
 int /*<<< orphan*/  ssl_security_cert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssl_security_cert_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int ssl_security_cert(SSL *s, SSL_CTX *ctx, X509 *x, int vfy, int is_ee)
{
    if (vfy)
        vfy = SSL_SECOP_PEER;
    if (is_ee) {
        if (!ssl_security_cert_key(s, ctx, x, SSL_SECOP_EE_KEY | vfy))
            return SSL_R_EE_KEY_TOO_SMALL;
    } else {
        if (!ssl_security_cert_key(s, ctx, x, SSL_SECOP_CA_KEY | vfy))
            return SSL_R_CA_KEY_TOO_SMALL;
    }
    if (!ssl_security_cert_sig(s, ctx, x, SSL_SECOP_CA_MD | vfy))
        return SSL_R_CA_MD_TOO_WEAK;
    return 1;
}