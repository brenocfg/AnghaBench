#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t length; unsigned char const* data; } ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ EVP_PKEY ;
typedef  TYPE_2__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_GET0_POLY1305 ; 
 scalar_t__ EVP_PKEY_POLY1305 ; 
 TYPE_2__* EVP_PKEY_get0 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  EVP_R_EXPECTING_A_POLY1305_KEY ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const unsigned char *EVP_PKEY_get0_poly1305(const EVP_PKEY *pkey, size_t *len)
{
    ASN1_OCTET_STRING *os = NULL;
    if (pkey->type != EVP_PKEY_POLY1305) {
        EVPerr(EVP_F_EVP_PKEY_GET0_POLY1305, EVP_R_EXPECTING_A_POLY1305_KEY);
        return NULL;
    }
    os = EVP_PKEY_get0(pkey);
    *len = os->length;
    return os->data;
}