#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_private_key ;
struct TYPE_4__ {void* rsa; } ;
struct TYPE_5__ {int /*<<< orphan*/ * md; int /*<<< orphan*/  signature_alg; TYPE_1__ private_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION ; 
 int /*<<< orphan*/  RSA_free (void*) ; 
 int /*<<< orphan*/  pkcs1_rsa_sha1_alg ; 

void
hx509_private_key_assign_rsa(hx509_private_key key, void *ptr)
{
    if (key->private_key.rsa)
	RSA_free(key->private_key.rsa);
    key->private_key.rsa = ptr;
    key->signature_alg = ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION;
    key->md = &pkcs1_rsa_sha1_alg;
}