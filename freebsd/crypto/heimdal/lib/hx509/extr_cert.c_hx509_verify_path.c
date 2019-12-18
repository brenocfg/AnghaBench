#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_70__   TYPE_9__ ;
typedef  struct TYPE_69__   TYPE_8__ ;
typedef  struct TYPE_68__   TYPE_7__ ;
typedef  struct TYPE_67__   TYPE_6__ ;
typedef  struct TYPE_66__   TYPE_5__ ;
typedef  struct TYPE_65__   TYPE_4__ ;
typedef  struct TYPE_64__   TYPE_3__ ;
typedef  struct TYPE_63__   TYPE_2__ ;
typedef  struct TYPE_62__   TYPE_29__ ;
typedef  struct TYPE_61__   TYPE_1__ ;
typedef  struct TYPE_60__   TYPE_12__ ;
typedef  struct TYPE_59__   TYPE_11__ ;
typedef  struct TYPE_58__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  proxy_issuer ;
typedef  TYPE_6__* hx509_verify_ctx ;
struct TYPE_68__ {size_t len; TYPE_9__** val; } ;
typedef  TYPE_7__ hx509_path ;
typedef  int /*<<< orphan*/  hx509_name_constraints ;
typedef  TYPE_8__* hx509_context ;
typedef  int /*<<< orphan*/ * hx509_certs ;
typedef  TYPE_9__* hx509_cert ;
typedef  enum certtype { ____Placeholder_certtype } certtype ;
struct TYPE_70__ {TYPE_12__* data; int /*<<< orphan*/  basename; } ;
struct TYPE_69__ {scalar_t__ default_trust_anchors; } ;
struct TYPE_67__ {int flags; scalar_t__ time_now; scalar_t__ revoke_ctx; int /*<<< orphan*/  max_depth; scalar_t__ trust_anchors; } ;
struct TYPE_65__ {int /*<<< orphan*/  notBefore; int /*<<< orphan*/  notAfter; } ;
struct TYPE_66__ {TYPE_4__ validity; int /*<<< orphan*/  _save; int /*<<< orphan*/  subject; int /*<<< orphan*/  issuer; } ;
struct TYPE_63__ {size_t len; TYPE_29__* val; } ;
struct TYPE_64__ {TYPE_2__ rdnSequence; } ;
struct TYPE_62__ {int len; TYPE_1__* val; } ;
struct TYPE_61__ {int /*<<< orphan*/  type; } ;
struct TYPE_60__ {int /*<<< orphan*/  signatureAlgorithm; TYPE_5__ tbsCertificate; int /*<<< orphan*/  signatureValue; } ;
struct TYPE_59__ {TYPE_3__ u; } ;
struct TYPE_58__ {size_t* pCPathLenConstraint; } ;
typedef  TYPE_10__ ProxyCertInfo ;
typedef  TYPE_11__ Name ;
typedef  TYPE_12__ Certificate ;

/* Variables and functions */
 scalar_t__ ALLOW_DEF_TA (TYPE_6__*) ; 
#define  CA_CERT 130 
 scalar_t__ CHECK_TA (TYPE_6__*) ; 
#define  EE_CERT 129 
 int /*<<< orphan*/  FALSE ; 
 int HX509_CERT_USED_AFTER_TIME ; 
 int HX509_CERT_USED_BEFORE_TIME ; 
 int /*<<< orphan*/  HX509_ERROR_APPEND ; 
 int HX509_PATH_TOO_LONG ; 
 int HX509_PROXY_CERT_INVALID ; 
 int HX509_PROXY_CERT_NAME_WRONG ; 
 int HX509_VERIFY_CTX_F_ALLOW_PROXY_CERTIFICATE ; 
 int HX509_VERIFY_CTX_F_NO_BEST_BEFORE_CHECK ; 
 int HX509_VERIFY_CTX_F_TIME_SET ; 
#define  PROXY_CERT 128 
 int /*<<< orphan*/  REQUIRE_RFC3280 (TYPE_6__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _hx509_Time2time_t (int /*<<< orphan*/ *) ; 
 int _hx509_calculate_path (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_12__* _hx509_get_cert (TYPE_9__*) ; 
 int _hx509_name_cmp (TYPE_11__*,int /*<<< orphan*/ *,int*) ; 
 int _hx509_name_from_Name (TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_path_free (TYPE_7__*) ; 
 int _hx509_signature_best_before (TYPE_8__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int _hx509_verify_signature_bitstring (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int add_name_constraints (TYPE_8__*,TYPE_12__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asn1_oid_id_at_commonName ; 
 int /*<<< orphan*/  asn1_oid_id_x509_ce_issuerAltName ; 
 int /*<<< orphan*/  asn1_oid_id_x509_ce_subjectAltName ; 
 int certificate_is_self_signed (TYPE_8__*,TYPE_12__*,int*) ; 
 int check_basic_constraints (TYPE_8__*,TYPE_12__*,int,size_t) ; 
 int check_key_usage (TYPE_8__*,TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 int check_name_constraints (TYPE_8__*,int /*<<< orphan*/ *,TYPE_12__*) ; 
 int copy_Name (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_extension (TYPE_12__*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_Name (TYPE_11__*) ; 
 int /*<<< orphan*/  free_ProxyCertInfo (TYPE_10__*) ; 
 int /*<<< orphan*/  free_RelativeDistinguishedName (TYPE_29__*) ; 
 int /*<<< orphan*/  free_name_constraints (int /*<<< orphan*/ *) ; 
 int hx509_certs_add (TYPE_8__*,int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (TYPE_8__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int hx509_certs_merge (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hx509_certs_ref (scalar_t__) ; 
 int /*<<< orphan*/  hx509_clear_error_string (TYPE_8__*) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int hx509_revoke_verify (TYPE_8__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,TYPE_9__*,TYPE_9__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (TYPE_8__*,int /*<<< orphan*/ ,int,char*) ; 
 int init_name_constraints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_proxy_cert (TYPE_8__*,TYPE_12__*,TYPE_10__*) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
hx509_verify_path(hx509_context context,
		  hx509_verify_ctx ctx,
		  hx509_cert cert,
		  hx509_certs pool)
{
    hx509_name_constraints nc;
    hx509_path path;
    int ret, proxy_cert_depth, selfsigned_depth, diff;
    size_t i, k;
    enum certtype type;
    Name proxy_issuer;
    hx509_certs anchors = NULL;

    memset(&proxy_issuer, 0, sizeof(proxy_issuer));

    ret = init_name_constraints(&nc);
    if (ret)
	return ret;

    path.val = NULL;
    path.len = 0;

    if ((ctx->flags & HX509_VERIFY_CTX_F_TIME_SET) == 0)
	ctx->time_now = time(NULL);

    /*
     *
     */
    if (ctx->trust_anchors)
	anchors = hx509_certs_ref(ctx->trust_anchors);
    else if (context->default_trust_anchors && ALLOW_DEF_TA(ctx))
	anchors = hx509_certs_ref(context->default_trust_anchors);
    else {
	ret = hx509_certs_init(context, "MEMORY:no-TA", 0, NULL, &anchors);
	if (ret)
	    goto out;
    }

    /*
     * Calculate the path from the certificate user presented to the
     * to an anchor.
     */
    ret = _hx509_calculate_path(context, 0, ctx->time_now,
				anchors, ctx->max_depth,
				cert, pool, &path);
    if (ret)
	goto out;

    /*
     * Check CA and proxy certificate chain from the top of the
     * certificate chain. Also check certificate is valid with respect
     * to the current time.
     *
     */

    proxy_cert_depth = 0;
    selfsigned_depth = 0;

    if (ctx->flags & HX509_VERIFY_CTX_F_ALLOW_PROXY_CERTIFICATE)
	type = PROXY_CERT;
    else
	type = EE_CERT;

    for (i = 0; i < path.len; i++) {
	Certificate *c;
	time_t t;

	c = _hx509_get_cert(path.val[i]);

	/*
	 * Lets do some basic check on issuer like
	 * keyUsage.keyCertSign and basicConstraints.cA bit depending
	 * on what type of certificate this is.
	 */

	switch (type) {
	case CA_CERT:

	    /* XXX make constants for keyusage */
	    ret = check_key_usage(context, c, 1 << 5,
				  REQUIRE_RFC3280(ctx) ? TRUE : FALSE);
	    if (ret) {
		hx509_set_error_string(context, HX509_ERROR_APPEND, ret,
				       "Key usage missing from CA certificate");
		goto out;
	    }

	    /* self signed cert doesn't add to path length */
	    if (i + 1 != path.len) {
		int selfsigned;

		ret = certificate_is_self_signed(context, c, &selfsigned);
		if (ret)
		    goto out;
		if (selfsigned)
		    selfsigned_depth++;
	    }

	    break;
	case PROXY_CERT: {
	    ProxyCertInfo info;

	    if (is_proxy_cert(context, c, &info) == 0) {
		size_t j;

		if (info.pCPathLenConstraint != NULL &&
		    *info.pCPathLenConstraint < i)
		{
		    free_ProxyCertInfo(&info);
		    ret = HX509_PATH_TOO_LONG;
		    hx509_set_error_string(context, 0, ret,
					   "Proxy certificate chain "
					   "longer then allowed");
		    goto out;
		}
		/* XXX MUST check info.proxyPolicy */
		free_ProxyCertInfo(&info);

		j = 0;
		if (find_extension(c, &asn1_oid_id_x509_ce_subjectAltName, &j)) {
		    ret = HX509_PROXY_CERT_INVALID;
		    hx509_set_error_string(context, 0, ret,
					   "Proxy certificate have explicity "
					   "forbidden subjectAltName");
		    goto out;
		}

		j = 0;
		if (find_extension(c, &asn1_oid_id_x509_ce_issuerAltName, &j)) {
		    ret = HX509_PROXY_CERT_INVALID;
		    hx509_set_error_string(context, 0, ret,
					   "Proxy certificate have explicity "
					   "forbidden issuerAltName");
		    goto out;
		}

		/*
		 * The subject name of the proxy certificate should be
		 * CN=XXX,<proxy issuer>, prune of CN and check if its
		 * the same over the whole chain of proxy certs and
		 * then check with the EE cert when we get to it.
		 */

		if (proxy_cert_depth) {
		    ret = _hx509_name_cmp(&proxy_issuer, &c->tbsCertificate.subject, &diff);
		    if (ret) {
			hx509_set_error_string(context, 0, ret, "Out of memory");
			goto out;
		    }
		    if (diff) {
			ret = HX509_PROXY_CERT_NAME_WRONG;
			hx509_set_error_string(context, 0, ret,
					       "Base proxy name not right");
			goto out;
		    }
		}

		free_Name(&proxy_issuer);

		ret = copy_Name(&c->tbsCertificate.subject, &proxy_issuer);
		if (ret) {
		    hx509_clear_error_string(context);
		    goto out;
		}

		j = proxy_issuer.u.rdnSequence.len;
		if (proxy_issuer.u.rdnSequence.len < 2
		    || proxy_issuer.u.rdnSequence.val[j - 1].len > 1
		    || der_heim_oid_cmp(&proxy_issuer.u.rdnSequence.val[j - 1].val[0].type,
					&asn1_oid_id_at_commonName))
		{
		    ret = HX509_PROXY_CERT_NAME_WRONG;
		    hx509_set_error_string(context, 0, ret,
					   "Proxy name too short or "
					   "does not have Common name "
					   "at the top");
		    goto out;
		}

		free_RelativeDistinguishedName(&proxy_issuer.u.rdnSequence.val[j - 1]);
		proxy_issuer.u.rdnSequence.len -= 1;

		ret = _hx509_name_cmp(&proxy_issuer, &c->tbsCertificate.issuer, &diff);
		if (ret) {
		    hx509_set_error_string(context, 0, ret, "Out of memory");
		    goto out;
		}
		if (diff != 0) {
		    ret = HX509_PROXY_CERT_NAME_WRONG;
		    hx509_set_error_string(context, 0, ret,
					   "Proxy issuer name not as expected");
		    goto out;
		}

		break;
	    } else {
		/*
		 * Now we are done with the proxy certificates, this
		 * cert was an EE cert and we we will fall though to
		 * EE checking below.
		 */
		type = EE_CERT;
		/* FALLTHOUGH */
	    }
	}
	case EE_CERT:
	    /*
	     * If there where any proxy certificates in the chain
	     * (proxy_cert_depth > 0), check that the proxy issuer
	     * matched proxy certificates "base" subject.
	     */
	    if (proxy_cert_depth) {

		ret = _hx509_name_cmp(&proxy_issuer,
				      &c->tbsCertificate.subject, &diff);
		if (ret) {
		    hx509_set_error_string(context, 0, ret, "out of memory");
		    goto out;
		}
		if (diff) {
		    ret = HX509_PROXY_CERT_NAME_WRONG;
		    hx509_clear_error_string(context);
		    goto out;
		}
		if (cert->basename)
		    hx509_name_free(&cert->basename);

		ret = _hx509_name_from_Name(&proxy_issuer, &cert->basename);
		if (ret) {
		    hx509_clear_error_string(context);
		    goto out;
		}
	    }

	    break;
	}

	ret = check_basic_constraints(context, c, type,
				      i - proxy_cert_depth - selfsigned_depth);
	if (ret)
	    goto out;

	/*
	 * Don't check the trust anchors expiration time since they
	 * are transported out of band, from RFC3820.
	 */
	if (i + 1 != path.len || CHECK_TA(ctx)) {

	    t = _hx509_Time2time_t(&c->tbsCertificate.validity.notBefore);
	    if (t > ctx->time_now) {
		ret = HX509_CERT_USED_BEFORE_TIME;
		hx509_clear_error_string(context);
		goto out;
	    }
	    t = _hx509_Time2time_t(&c->tbsCertificate.validity.notAfter);
	    if (t < ctx->time_now) {
		ret = HX509_CERT_USED_AFTER_TIME;
		hx509_clear_error_string(context);
		goto out;
	    }
	}

	if (type == EE_CERT)
	    type = CA_CERT;
	else if (type == PROXY_CERT)
	    proxy_cert_depth++;
    }

    /*
     * Verify constraints, do this backward so path constraints are
     * checked in the right order.
     */

    for (ret = 0, k = path.len; k > 0; k--) {
	Certificate *c;
	int selfsigned;
	i = k - 1;

	c = _hx509_get_cert(path.val[i]);

	ret = certificate_is_self_signed(context, c, &selfsigned);
	if (ret)
	    goto out;

	/* verify name constraints, not for selfsigned and anchor */
	if (!selfsigned || i + 1 != path.len) {
	    ret = check_name_constraints(context, &nc, c);
	    if (ret) {
		goto out;
	    }
	}
	ret = add_name_constraints(context, c, i == 0, &nc);
	if (ret)
	    goto out;

	/* XXX verify all other silly constraints */

    }

    /*
     * Verify that no certificates has been revoked.
     */

    if (ctx->revoke_ctx) {
	hx509_certs certs;

	ret = hx509_certs_init(context, "MEMORY:revoke-certs", 0,
			       NULL, &certs);
	if (ret)
	    goto out;

	for (i = 0; i < path.len; i++) {
	    ret = hx509_certs_add(context, certs, path.val[i]);
	    if (ret) {
		hx509_certs_free(&certs);
		goto out;
	    }
	}
	ret = hx509_certs_merge(context, certs, pool);
	if (ret) {
	    hx509_certs_free(&certs);
	    goto out;
	}

	for (i = 0; i < path.len - 1; i++) {
	    size_t parent = (i < path.len - 1) ? i + 1 : i;

	    ret = hx509_revoke_verify(context,
				      ctx->revoke_ctx,
				      certs,
				      ctx->time_now,
				      path.val[i],
				      path.val[parent]);
	    if (ret) {
		hx509_certs_free(&certs);
		goto out;
	    }
	}
	hx509_certs_free(&certs);
    }

    /*
     * Verify signatures, do this backward so public key working
     * parameter is passed up from the anchor up though the chain.
     */

    for (k = path.len; k > 0; k--) {
	hx509_cert signer;
	Certificate *c;
	i = k - 1;

	c = _hx509_get_cert(path.val[i]);

	/* is last in chain (trust anchor) */
	if (i + 1 == path.len) {
	    int selfsigned;

	    signer = path.val[i];

	    ret = certificate_is_self_signed(context, signer->data, &selfsigned);
	    if (ret)
		goto out;

	    /* if trust anchor is not self signed, don't check sig */
	    if (!selfsigned)
		continue;
	} else {
	    /* take next certificate in chain */
	    signer = path.val[i + 1];
	}

	/* verify signatureValue */
	ret = _hx509_verify_signature_bitstring(context,
						signer,
						&c->signatureAlgorithm,
						&c->tbsCertificate._save,
						&c->signatureValue);
	if (ret) {
	    hx509_set_error_string(context, HX509_ERROR_APPEND, ret,
				   "Failed to verify signature of certificate");
	    goto out;
	}
	/*
	 * Verify that the sigature algorithm "best-before" date is
	 * before the creation date of the certificate, do this for
	 * trust anchors too, since any trust anchor that is created
	 * after a algorithm is known to be bad deserved to be invalid.
	 *
	 * Skip the leaf certificate for now...
	 */

	if (i != 0 && (ctx->flags & HX509_VERIFY_CTX_F_NO_BEST_BEFORE_CHECK) == 0) {
	    time_t notBefore =
		_hx509_Time2time_t(&c->tbsCertificate.validity.notBefore);
	    ret = _hx509_signature_best_before(context,
					       &c->signatureAlgorithm,
					       notBefore);
	    if (ret)
		goto out;
	}
    }

out:
    hx509_certs_free(&anchors);
    free_Name(&proxy_issuer);
    free_name_constraints(&nc);
    _hx509_path_free(&path);

    return ret;
}