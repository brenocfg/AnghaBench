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
struct hx509_generate_private_context {int /*<<< orphan*/  const* key_oid; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_RSAENCRYPTION ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct hx509_generate_private_context* calloc (int,int) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
_hx509_generate_private_key_init(hx509_context context,
				 const heim_oid *oid,
				 struct hx509_generate_private_context **ctx)
{
    *ctx = NULL;

    if (der_heim_oid_cmp(oid, ASN1_OID_ID_PKCS1_RSAENCRYPTION) != 0) {
	hx509_set_error_string(context, 0, EINVAL,
			       "private key not an RSA key");
	return EINVAL;
    }

    *ctx = calloc(1, sizeof(**ctx));
    if (*ctx == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }
    (*ctx)->key_oid = oid;

    return 0;
}