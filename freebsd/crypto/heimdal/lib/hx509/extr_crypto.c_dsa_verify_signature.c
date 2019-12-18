#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct signature_alg {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_18__ {int /*<<< orphan*/  length; scalar_t__ data; } ;
typedef  TYPE_5__ heim_octet_string ;
struct TYPE_17__ {TYPE_3__* parameters; } ;
struct TYPE_15__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {TYPE_4__ algorithm; TYPE_2__ subjectPublicKey; } ;
struct TYPE_14__ {TYPE_6__ subjectPublicKeyInfo; } ;
struct TYPE_21__ {TYPE_1__ tbsCertificate; } ;
struct TYPE_20__ {int /*<<< orphan*/  g; int /*<<< orphan*/  q; int /*<<< orphan*/  p; } ;
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ SubjectPublicKeyInfo ;
typedef  int /*<<< orphan*/  DSAPublicKey ;
typedef  TYPE_7__ DSAParams ;
typedef  int /*<<< orphan*/  DSA ;
typedef  TYPE_8__ Certificate ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int DSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DSA_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DSA_verify (int,scalar_t__,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int HX509_CRYPTO_BAD_SIGNATURE ; 
 int HX509_CRYPTO_SIG_INVALID_FORMAT ; 
 int decode_DSAParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,size_t*) ; 
 int decode_DSAPublicKey (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_DSAParams (TYPE_7__*) ; 
 int /*<<< orphan*/  free_DSAPublicKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heim_int2BN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
dsa_verify_signature(hx509_context context,
		     const struct signature_alg *sig_alg,
		     const Certificate *signer,
		     const AlgorithmIdentifier *alg,
		     const heim_octet_string *data,
		     const heim_octet_string *sig)
{
    const SubjectPublicKeyInfo *spi;
    DSAPublicKey pk;
    DSAParams param;
    size_t size;
    BIGNUM *key, *p, *q, *g;
    DSA *dsa;
    int ret;

    spi = &signer->tbsCertificate.subjectPublicKeyInfo;

    dsa = DSA_new();
    if (dsa == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    ret = decode_DSAPublicKey(spi->subjectPublicKey.data,
			      spi->subjectPublicKey.length / 8,
			      &pk, &size);
    if (ret)
	goto out;

    key = heim_int2BN(&pk);

    free_DSAPublicKey(&pk);

    if (key == NULL) {
	ret = ENOMEM;
	hx509_set_error_string(context, 0, ret, "out of memory");
	goto out;
    }

    ret = DSA_set0_key(dsa, key, NULL);

    if (ret != 1) {
	BN_free(key);
	ret = EINVAL;
	hx509_set_error_string(context, 0, ret, "failed to set DSA key");
	goto out;
    }

    if (spi->algorithm.parameters == NULL) {
	ret = HX509_CRYPTO_SIG_INVALID_FORMAT;
	hx509_set_error_string(context, 0, ret, "DSA parameters missing");
	goto out;
    }

    ret = decode_DSAParams(spi->algorithm.parameters->data,
			   spi->algorithm.parameters->length,
			   &param,
			   &size);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "DSA parameters failed to decode");
	goto out;
    }

    p = heim_int2BN(&param.p);
    q = heim_int2BN(&param.q);
    g = heim_int2BN(&param.g);

    free_DSAParams(&param);

    if (p == NULL || q == NULL || g == NULL) {
	BN_free(p);
	BN_free(q);
	BN_free(g);
	ret = ENOMEM;
	hx509_set_error_string(context, 0, ret, "out of memory");
	goto out;
    }

    ret = DSA_set0_pqg(dsa, p, q, g);

    if (ret != 1) {
	BN_free(p);
	BN_free(q);
	BN_free(g);
	ret = EINVAL;
	hx509_set_error_string(context, 0, ret, "failed to set DSA parameters");
	goto out;
    }

    ret = DSA_verify(-1, data->data, data->length,
		     (unsigned char*)sig->data, sig->length,
		     dsa);
    if (ret == 1)
	ret = 0;
    else if (ret == 0 || ret == -1) {
	ret = HX509_CRYPTO_BAD_SIGNATURE;
	hx509_set_error_string(context, 0, ret, "BAD DSA sigature");
    } else {
	ret = HX509_CRYPTO_SIG_INVALID_FORMAT;
	hx509_set_error_string(context, 0, ret, "Invalid format of DSA sigature");
    }

 out:
    DSA_free(dsa);

    return ret;
}