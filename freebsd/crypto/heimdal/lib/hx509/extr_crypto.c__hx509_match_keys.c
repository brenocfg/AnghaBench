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
typedef  TYPE_2__* hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  key_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_ECPUBLICKEY ; 
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_RSAENCRYPTION ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int match_keys_ec (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int match_keys_rsa (int /*<<< orphan*/ ,TYPE_2__*) ; 

int
_hx509_match_keys(hx509_cert c, hx509_private_key key)
{
    if (der_heim_oid_cmp(key->ops->key_oid, ASN1_OID_ID_PKCS1_RSAENCRYPTION) == 0)
	return match_keys_rsa(c, key);
    if (der_heim_oid_cmp(key->ops->key_oid, ASN1_OID_ID_ECPUBLICKEY) == 0)
	return match_keys_ec(c, key);
    return 0;

}