#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct signature_alg {int flags; int (* verify_signature ) (int /*<<< orphan*/ ,struct signature_alg const*,TYPE_4__ const*,TYPE_5__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;scalar_t__ key_oid; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  scalar_t__ hx509_cert ;
typedef  int /*<<< orphan*/  heim_octet_string ;
struct TYPE_14__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_11__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_12__ {TYPE_2__ algorithm; } ;
struct TYPE_10__ {TYPE_3__ subjectPublicKeyInfo; } ;
struct TYPE_13__ {TYPE_1__ tbsCertificate; } ;
typedef  TYPE_3__ SubjectPublicKeyInfo ;
typedef  TYPE_4__ Certificate ;
typedef  TYPE_5__ AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_CRYPTO_SIGNATURE_WITHOUT_SIGNER ; 
 int HX509_CRYPTO_SIG_NO_CONF ; 
 int HX509_SIG_ALG_DONT_MATCH_KEY_ALG ; 
 int HX509_SIG_ALG_NO_SUPPORTED ; 
 int PROVIDE_CONF ; 
 int REQUIRE_SIGNER ; 
 TYPE_4__* _hx509_get_cert (scalar_t__ const) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,scalar_t__) ; 
 struct signature_alg* find_sig_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct signature_alg const*,TYPE_4__ const*,TYPE_5__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
_hx509_verify_signature(hx509_context context,
			const hx509_cert cert,
			const AlgorithmIdentifier *alg,
			const heim_octet_string *data,
			const heim_octet_string *sig)
{
    const struct signature_alg *md;
    const Certificate *signer = NULL;

    if (cert)
	signer = _hx509_get_cert(cert);

    md = find_sig_alg(&alg->algorithm);
    if (md == NULL) {
	hx509_clear_error_string(context);
	return HX509_SIG_ALG_NO_SUPPORTED;
    }
    if (signer && (md->flags & PROVIDE_CONF) == 0) {
	hx509_clear_error_string(context);
	return HX509_CRYPTO_SIG_NO_CONF;
    }
    if (signer == NULL && (md->flags & REQUIRE_SIGNER)) {
	    hx509_clear_error_string(context);
	return HX509_CRYPTO_SIGNATURE_WITHOUT_SIGNER;
    }
    if (md->key_oid && signer) {
	const SubjectPublicKeyInfo *spi;
	spi = &signer->tbsCertificate.subjectPublicKeyInfo;

	if (der_heim_oid_cmp(&spi->algorithm.algorithm, md->key_oid) != 0) {
	    hx509_clear_error_string(context);
	    return HX509_SIG_ALG_DONT_MATCH_KEY_ALG;
	}
    }
    return (*md->verify_signature)(context, md, signer, alg, data, sig);
}