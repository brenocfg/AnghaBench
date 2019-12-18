#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct signature_alg {int flags; TYPE_3__* digest_alg; } ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_22__ {size_t length; scalar_t__ data; } ;
typedef  TYPE_5__ heim_octet_string ;
typedef  int /*<<< orphan*/  di ;
struct TYPE_19__ {unsigned char* data; int length; } ;
struct TYPE_23__ {TYPE_2__ subjectPublicKey; } ;
struct TYPE_18__ {TYPE_6__ subjectPublicKeyInfo; } ;
struct TYPE_25__ {TYPE_1__ tbsCertificate; } ;
struct TYPE_17__ {TYPE_4__* parameters; int /*<<< orphan*/  algorithm; } ;
struct TYPE_24__ {int /*<<< orphan*/  digest; TYPE_15__ digestAlgorithm; } ;
struct TYPE_21__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_6__ SubjectPublicKeyInfo ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_7__ DigestInfo ;
typedef  TYPE_8__ Certificate ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int HX509_CRYPTO_OID_MISMATCH ; 
 int HX509_CRYPTO_SIG_INVALID_FORMAT ; 
 int RA_RSA_USES_DIGEST_INFO ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int RSA_public_decrypt (size_t,unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int _hx509_verify_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_15__*,TYPE_5__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ct_memcmp (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/ * d2i_RSAPublicKey (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int decode_DigestInfo (unsigned char*,int,TYPE_7__*,size_t*) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  free_DigestInfo (TYPE_7__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 unsigned char* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rsa_verify_signature(hx509_context context,
		     const struct signature_alg *sig_alg,
		     const Certificate *signer,
		     const AlgorithmIdentifier *alg,
		     const heim_octet_string *data,
		     const heim_octet_string *sig)
{
    const SubjectPublicKeyInfo *spi;
    DigestInfo di;
    unsigned char *to;
    int tosize, retsize;
    int ret;
    RSA *rsa;
    size_t size;
    const unsigned char *p;

    memset(&di, 0, sizeof(di));

    spi = &signer->tbsCertificate.subjectPublicKeyInfo;

    p = spi->subjectPublicKey.data;
    size = spi->subjectPublicKey.length / 8;

    rsa = d2i_RSAPublicKey(NULL, &p, size);
    if (rsa == NULL) {
	ret = ENOMEM;
	hx509_set_error_string(context, 0, ret, "out of memory");
	goto out;
    }

    tosize = RSA_size(rsa);
    to = malloc(tosize);
    if (to == NULL) {
	ret = ENOMEM;
	hx509_set_error_string(context, 0, ret, "out of memory");
	goto out;
    }

    retsize = RSA_public_decrypt(sig->length, (unsigned char *)sig->data,
				 to, rsa, RSA_PKCS1_PADDING);
    if (retsize <= 0) {
	ret = HX509_CRYPTO_SIG_INVALID_FORMAT;
	hx509_set_error_string(context, 0, ret,
			       "RSA public decrypt failed: %d", retsize);
	free(to);
	goto out;
    }
    if (retsize > tosize)
	_hx509_abort("internal rsa decryption failure: ret > tosize");

    if (sig_alg->flags & RA_RSA_USES_DIGEST_INFO) {

	ret = decode_DigestInfo(to, retsize, &di, &size);
	free(to);
	if (ret) {
	    goto out;
	}

	/* Check for extra data inside the sigature */
	if (size != (size_t)retsize) {
	    ret = HX509_CRYPTO_SIG_INVALID_FORMAT;
	    hx509_set_error_string(context, 0, ret, "size from decryption mismatch");
	    goto out;
	}

	if (sig_alg->digest_alg &&
	    der_heim_oid_cmp(&di.digestAlgorithm.algorithm,
			     &sig_alg->digest_alg->algorithm) != 0)
	{
	    ret = HX509_CRYPTO_OID_MISMATCH;
	    hx509_set_error_string(context, 0, ret, "object identifier in RSA sig mismatch");
	    goto out;
	}

	/* verify that the parameters are NULL or the NULL-type */
	if (di.digestAlgorithm.parameters != NULL &&
	    (di.digestAlgorithm.parameters->length != 2 ||
	     memcmp(di.digestAlgorithm.parameters->data, "\x05\x00", 2) != 0))
	{
	    ret = HX509_CRYPTO_SIG_INVALID_FORMAT;
	    hx509_set_error_string(context, 0, ret, "Extra parameters inside RSA signature");
	    goto out;
	}

	ret = _hx509_verify_signature(context,
				      NULL,
				      &di.digestAlgorithm,
				      data,
				      &di.digest);
    } else {
	if ((size_t)retsize != data->length ||
	    ct_memcmp(to, data->data, retsize) != 0)
	{
	    ret = HX509_CRYPTO_SIG_INVALID_FORMAT;
	    hx509_set_error_string(context, 0, ret, "RSA Signature incorrect");
	    goto out;
	}
	free(to);
    }
    ret = 0;

 out:
    free_DigestInfo(&di);
    if (rsa)
	RSA_free(rsa);
    return ret;
}