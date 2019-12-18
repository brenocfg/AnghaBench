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
struct wpabuf {int dummy; } ;
struct TYPE_7__ {TYPE_1__* pub_key; int /*<<< orphan*/  alg; } ;
struct TYPE_6__ {unsigned char* data; size_t length; int flags; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_2__ DPP_BOOTSTRAPPING_KEY ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int ASN1_STRING_FLAG_BITS_LEFT ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  DPP_BOOTSTRAPPING_KEY_free (TYPE_2__*) ; 
 TYPE_2__* DPP_BOOTSTRAPPING_KEY_new () ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 size_t EC_POINT_point2oct (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_EC ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  POINT_CONVERSION_COMPRESSED ; 
 int /*<<< orphan*/  V_ASN1_OBJECT ; 
 int X509_ALGOR_set0 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dpp_debug_print_point (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int i2d_DPP_BOOTSTRAPPING_KEY (TYPE_2__*,unsigned char**) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc_copy (unsigned char*,int) ; 

__attribute__((used)) static struct wpabuf * dpp_bootstrap_key_der(EVP_PKEY *key)
{
	unsigned char *der = NULL;
	int der_len;
	EC_KEY *eckey;
	struct wpabuf *ret = NULL;
	size_t len;
	const EC_GROUP *group;
	const EC_POINT *point;
	BN_CTX *ctx;
	DPP_BOOTSTRAPPING_KEY *bootstrap = NULL;
	int nid;

	ctx = BN_CTX_new();
	eckey = EVP_PKEY_get1_EC_KEY(key);
	if (!ctx || !eckey)
		goto fail;

	group = EC_KEY_get0_group(eckey);
	point = EC_KEY_get0_public_key(eckey);
	if (!group || !point)
		goto fail;
	dpp_debug_print_point("DPP: bootstrap public key", group, point);
	nid = EC_GROUP_get_curve_name(group);

	bootstrap = DPP_BOOTSTRAPPING_KEY_new();
	if (!bootstrap ||
	    X509_ALGOR_set0(bootstrap->alg, OBJ_nid2obj(EVP_PKEY_EC),
			    V_ASN1_OBJECT, (void *) OBJ_nid2obj(nid)) != 1)
		goto fail;

	len = EC_POINT_point2oct(group, point, POINT_CONVERSION_COMPRESSED,
				 NULL, 0, ctx);
	if (len == 0)
		goto fail;

	der = OPENSSL_malloc(len);
	if (!der)
		goto fail;
	len = EC_POINT_point2oct(group, point, POINT_CONVERSION_COMPRESSED,
				 der, len, ctx);

	OPENSSL_free(bootstrap->pub_key->data);
	bootstrap->pub_key->data = der;
	der = NULL;
	bootstrap->pub_key->length = len;
	/* No unused bits */
	bootstrap->pub_key->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT | 0x07);
	bootstrap->pub_key->flags |= ASN1_STRING_FLAG_BITS_LEFT;

	der_len = i2d_DPP_BOOTSTRAPPING_KEY(bootstrap, &der);
	if (der_len <= 0) {
		wpa_printf(MSG_ERROR,
			   "DDP: Failed to build DER encoded public key");
		goto fail;
	}

	ret = wpabuf_alloc_copy(der, der_len);
fail:
	DPP_BOOTSTRAPPING_KEY_free(bootstrap);
	OPENSSL_free(der);
	EC_KEY_free(eckey);
	BN_CTX_free(ctx);
	return ret;
}