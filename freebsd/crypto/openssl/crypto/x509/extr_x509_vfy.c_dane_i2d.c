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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
#define  DANETLS_SELECTOR_CERT 129 
#define  DANETLS_SELECTOR_SPKI 128 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509_F_DANE_I2D ; 
 int /*<<< orphan*/  X509_R_BAD_SELECTOR ; 
 int /*<<< orphan*/  X509_get_X509_PUBKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2d_X509 (int /*<<< orphan*/ *,unsigned char**) ; 
 int i2d_X509_PUBKEY (int /*<<< orphan*/ ,unsigned char**) ; 

__attribute__((used)) static unsigned char *dane_i2d(
    X509 *cert,
    uint8_t selector,
    unsigned int *i2dlen)
{
    unsigned char *buf = NULL;
    int len;

    /*
     * Extract ASN.1 DER form of certificate or public key.
     */
    switch (selector) {
    case DANETLS_SELECTOR_CERT:
        len = i2d_X509(cert, &buf);
        break;
    case DANETLS_SELECTOR_SPKI:
        len = i2d_X509_PUBKEY(X509_get_X509_PUBKEY(cert), &buf);
        break;
    default:
        X509err(X509_F_DANE_I2D, X509_R_BAD_SELECTOR);
        return NULL;
    }

    if (len < 0 || buf == NULL) {
        X509err(X509_F_DANE_I2D, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    *i2dlen = (unsigned int)len;
    return buf;
}