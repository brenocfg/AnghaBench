#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* hx509_private_key ;
struct TYPE_7__ {int /*<<< orphan*/ * rsa; scalar_t__ ecdsa; } ;
struct TYPE_8__ {scalar_t__ ref; TYPE_2__ private_key; TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  key_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_ECPUBLICKEY ; 
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_RSAENCRYPTION ; 
 int /*<<< orphan*/  EC_KEY_free (scalar_t__) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

int
hx509_private_key_free(hx509_private_key *key)
{
    if (key == NULL || *key == NULL)
	return 0;

    if ((*key)->ref == 0)
	_hx509_abort("key refcount == 0 on free");
    if (--(*key)->ref > 0)
	return 0;

    if ((*key)->ops && der_heim_oid_cmp((*key)->ops->key_oid, ASN1_OID_ID_PKCS1_RSAENCRYPTION) == 0) {
	if ((*key)->private_key.rsa)
	    RSA_free((*key)->private_key.rsa);
#ifdef HAVE_OPENSSL
    } else if ((*key)->ops && der_heim_oid_cmp((*key)->ops->key_oid, ASN1_OID_ID_ECPUBLICKEY) == 0) {
	if ((*key)->private_key.ecdsa)
	    EC_KEY_free((*key)->private_key.ecdsa);
#endif
    }
    (*key)->private_key.rsa = NULL;
    free(*key);
    *key = NULL;
    return 0;
}