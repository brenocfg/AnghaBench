#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {unsigned int len; int /*<<< orphan*/ * val; } ;
struct TYPE_15__ {int len; TYPE_3__* val; } ;
struct TYPE_13__ {TYPE_10__* eContent; int /*<<< orphan*/  eContentType; } ;
struct TYPE_17__ {TYPE_10__* certificates; TYPE_8__ digestAlgorithms; TYPE_4__ signerInfos; TYPE_2__ encapContentInfo; int /*<<< orphan*/  version; } ;
struct TYPE_12__ {size_t length; int /*<<< orphan*/  data; } ;
struct sigctx {int leafonly; void* certs; TYPE_7__ sd; void* pool; void* anchors; int /*<<< orphan*/  cmsidflag; int /*<<< orphan*/  peer; int /*<<< orphan*/  const* eContentType; TYPE_1__ content; int /*<<< orphan*/  const* digest_alg; } ;
typedef  int /*<<< orphan*/  sigctx ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hx509_peer_info ;
typedef  struct sigctx hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  void* hx509_certs ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_16__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ heim_octet_string ;
struct TYPE_14__ {int /*<<< orphan*/  digestAlgorithm; } ;
struct TYPE_11__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (TYPE_10__*,int) ; 
 int /*<<< orphan*/  ASN1_MALLOC_ENCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,TYPE_7__*,size_t*,int) ; 
 int /*<<< orphan*/  CMSVersion_v3 ; 
 int /*<<< orphan*/  CMS_ID_NAME ; 
 int /*<<< orphan*/  CMS_ID_SKI ; 
 int ENOMEM ; 
 int HX509_CMS_SIGNATURE_DETACHED ; 
 int HX509_CMS_SIGNATURE_ID_NAME ; 
 int HX509_CMS_SIGNATURE_LEAF_ONLY ; 
 int HX509_CMS_SIGNATURE_NO_CERTS ; 
 int HX509_CMS_SIGNATURE_NO_SIGNER ; 
 int /*<<< orphan*/  SignedData ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int add_DigestAlgorithmIdentifiers (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_data ; 
 int /*<<< orphan*/  cert_process ; 
 scalar_t__ cmp_AlgorithmIdentifier (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_SignedData (TYPE_7__*) ; 
 int /*<<< orphan*/  hx509_certs_free (void**) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct sigctx*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  memset (struct sigctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_UNCONST (void const*) ; 
 int /*<<< orphan*/  sig_process ; 

int
hx509_cms_create_signed(hx509_context context,
			int flags,
			const heim_oid *eContentType,
			const void *data, size_t length,
			const AlgorithmIdentifier *digest_alg,
			hx509_certs certs,
			hx509_peer_info peer,
			hx509_certs anchors,
			hx509_certs pool,
			heim_octet_string *signed_data)
{
    unsigned int i, j;
    hx509_name name;
    int ret;
    size_t size;
    struct sigctx sigctx;

    memset(&sigctx, 0, sizeof(sigctx));
    memset(&name, 0, sizeof(name));

    if (eContentType == NULL)
	eContentType = &asn1_oid_id_pkcs7_data;

    sigctx.digest_alg = digest_alg;
    sigctx.content.data = rk_UNCONST(data);
    sigctx.content.length = length;
    sigctx.eContentType = eContentType;
    sigctx.peer = peer;
    /**
     * Use HX509_CMS_SIGNATURE_ID_NAME to preferred use of issuer name
     * and serial number if possible. Otherwise subject key identifier
     * will preferred.
     */
    if (flags & HX509_CMS_SIGNATURE_ID_NAME)
	sigctx.cmsidflag = CMS_ID_NAME;
    else
	sigctx.cmsidflag = CMS_ID_SKI;

    /**
     * Use HX509_CMS_SIGNATURE_LEAF_ONLY to only request leaf
     * certificates to be added to the SignedData.
     */
    sigctx.leafonly = (flags & HX509_CMS_SIGNATURE_LEAF_ONLY) ? 1 : 0;

    /**
     * Use HX509_CMS_NO_CERTS to make the SignedData contain no
     * certificates, overrides HX509_CMS_SIGNATURE_LEAF_ONLY.
     */

    if ((flags & HX509_CMS_SIGNATURE_NO_CERTS) == 0) {
	ret = hx509_certs_init(context, "MEMORY:certs", 0, NULL, &sigctx.certs);
	if (ret)
	    return ret;
    }

    sigctx.anchors = anchors;
    sigctx.pool = pool;

    sigctx.sd.version = CMSVersion_v3;

    der_copy_oid(eContentType, &sigctx.sd.encapContentInfo.eContentType);

    /**
     * Use HX509_CMS_SIGNATURE_DETACHED to create detached signatures.
     */
    if ((flags & HX509_CMS_SIGNATURE_DETACHED) == 0) {
	ALLOC(sigctx.sd.encapContentInfo.eContent, 1);
	if (sigctx.sd.encapContentInfo.eContent == NULL) {
	    hx509_clear_error_string(context);
	    ret = ENOMEM;
	    goto out;
	}

	sigctx.sd.encapContentInfo.eContent->data = malloc(length);
	if (sigctx.sd.encapContentInfo.eContent->data == NULL) {
	    hx509_clear_error_string(context);
	    ret = ENOMEM;
	    goto out;
	}
	memcpy(sigctx.sd.encapContentInfo.eContent->data, data, length);
	sigctx.sd.encapContentInfo.eContent->length = length;
    }

    /**
     * Use HX509_CMS_SIGNATURE_NO_SIGNER to create no sigInfo (no
     * signatures).
     */
    if ((flags & HX509_CMS_SIGNATURE_NO_SIGNER) == 0) {
	ret = hx509_certs_iter_f(context, certs, sig_process, &sigctx);
	if (ret)
	    goto out;
    }

    if (sigctx.sd.signerInfos.len) {

	/*
	 * For each signerInfo, collect all different digest types.
	 */
	for (i = 0; i < sigctx.sd.signerInfos.len; i++) {
	    AlgorithmIdentifier *di =
		&sigctx.sd.signerInfos.val[i].digestAlgorithm;

	    for (j = 0; j < sigctx.sd.digestAlgorithms.len; j++)
		if (cmp_AlgorithmIdentifier(di, &sigctx.sd.digestAlgorithms.val[j]) == 0)
		    break;
	    if (j == sigctx.sd.digestAlgorithms.len) {
		ret = add_DigestAlgorithmIdentifiers(&sigctx.sd.digestAlgorithms, di);
		if (ret) {
		    hx509_clear_error_string(context);
		    goto out;
		}
	    }
	}
    }

    /*
     * Add certs we think are needed, build as part of sig_process
     */
    if (sigctx.certs) {
	ALLOC(sigctx.sd.certificates, 1);
	if (sigctx.sd.certificates == NULL) {
	    hx509_clear_error_string(context);
	    ret = ENOMEM;
	    goto out;
	}

	ret = hx509_certs_iter_f(context, sigctx.certs, cert_process, &sigctx);
	if (ret)
	    goto out;
    }

    ASN1_MALLOC_ENCODE(SignedData,
		       signed_data->data, signed_data->length,
		       &sigctx.sd, &size, ret);
    if (ret) {
	hx509_clear_error_string(context);
	goto out;
    }
    if (signed_data->length != size)
	_hx509_abort("internal ASN.1 encoder error");

out:
    hx509_certs_free(&sigctx.certs);
    free_SignedData(&sigctx.sd);

    return ret;
}