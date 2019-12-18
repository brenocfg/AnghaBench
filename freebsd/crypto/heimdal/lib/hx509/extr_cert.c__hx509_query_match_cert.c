#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_24__ {int match; int (* cmp_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ timenow; int /*<<< orphan*/  expr; int /*<<< orphan*/  eku; int /*<<< orphan*/  keyhash_sha1; int /*<<< orphan*/  cmp_func_ctx; int /*<<< orphan*/  friendlyname; TYPE_1__* path; int /*<<< orphan*/  local_key_id; int /*<<< orphan*/  subject_id; int /*<<< orphan*/  subject_name; int /*<<< orphan*/  issuer_name; int /*<<< orphan*/  serial; int /*<<< orphan*/  certificate; int /*<<< orphan*/  subject; } ;
typedef  TYPE_6__ hx509_query ;
typedef  int /*<<< orphan*/ * hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_7__* hx509_cert_attribute ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_26__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_8__ heim_octet_string ;
struct TYPE_22__ {int /*<<< orphan*/  notAfter; int /*<<< orphan*/  notBefore; } ;
struct TYPE_20__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_21__ {TYPE_2__ subjectPublicKey; } ;
struct TYPE_23__ {TYPE_4__ validity; TYPE_3__ subjectPublicKeyInfo; int /*<<< orphan*/  subject; int /*<<< orphan*/  issuer; int /*<<< orphan*/  serialNumber; } ;
struct TYPE_27__ {TYPE_5__ tbsCertificate; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
struct TYPE_19__ {size_t len; int /*<<< orphan*/ * val; } ;
typedef  int /*<<< orphan*/  SubjectKeyIdentifier ;
typedef  TYPE_9__ Certificate ;

/* Variables and functions */
 int HX509_QUERY_ANCHOR ; 
 int HX509_QUERY_FIND_ISSUER_CERT ; 
 int HX509_QUERY_KU_CRLSIGN ; 
 int HX509_QUERY_KU_DATAENCIPHERMENT ; 
 int HX509_QUERY_KU_DIGITALSIGNATURE ; 
 int HX509_QUERY_KU_ENCIPHERMENT ; 
 int HX509_QUERY_KU_KEYAGREEMENT ; 
 int HX509_QUERY_KU_KEYCERTSIGN ; 
 int HX509_QUERY_KU_NONREPUDIATION ; 
 int HX509_QUERY_MASK ; 
 int HX509_QUERY_MATCH_CERTIFICATE ; 
 int HX509_QUERY_MATCH_EKU ; 
 int HX509_QUERY_MATCH_EXPR ; 
 int HX509_QUERY_MATCH_FRIENDLY_NAME ; 
 int HX509_QUERY_MATCH_FUNCTION ; 
 int HX509_QUERY_MATCH_ISSUER_ID ; 
 int HX509_QUERY_MATCH_ISSUER_NAME ; 
 int HX509_QUERY_MATCH_KEY_HASH_SHA1 ; 
 int HX509_QUERY_MATCH_LOCAL_KEY_ID ; 
 int HX509_QUERY_MATCH_SERIALNUMBER ; 
 int HX509_QUERY_MATCH_SUBJECT_KEY_ID ; 
 int HX509_QUERY_MATCH_SUBJECT_NAME ; 
 int HX509_QUERY_MATCH_TIME ; 
 int HX509_QUERY_NO_MATCH_PATH ; 
 int HX509_QUERY_PRIVATE_KEY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _hx509_Certificate_cmp (int /*<<< orphan*/ ,TYPE_9__*) ; 
 scalar_t__ _hx509_Time2time_t (int /*<<< orphan*/ *) ; 
 scalar_t__ _hx509_cert_is_parent_cmp (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _hx509_cert_private_key (int /*<<< orphan*/ ) ; 
 int _hx509_cert_to_env (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int _hx509_expr_eval (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _hx509_find_extension_subject_key_id (TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_9__* _hx509_get_cert (int /*<<< orphan*/ ) ; 
 int _hx509_name_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  _hx509_query_statistic (int /*<<< orphan*/ ,int,TYPE_6__ const*) ; 
 int _hx509_verify_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs_9_at_localKeyId ; 
 scalar_t__ check_key_usage (int /*<<< orphan*/ ,TYPE_9__*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ der_heim_integer_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ der_heim_octet_string_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_SubjectKeyIdentifier (int /*<<< orphan*/ *) ; 
 scalar_t__ hx509_cert_check_eku (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hx509_cert_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* hx509_cert_get_attribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* hx509_cert_get_friendly_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_env_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_signature_sha1 () ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_hx509_query_match_cert(hx509_context context, const hx509_query *q, hx509_cert cert)
{
    Certificate *c = _hx509_get_cert(cert);
    int ret, diff;

    _hx509_query_statistic(context, 1, q);

    if ((q->match & HX509_QUERY_FIND_ISSUER_CERT) &&
	_hx509_cert_is_parent_cmp(q->subject, c, 0) != 0)
	return 0;

    if ((q->match & HX509_QUERY_MATCH_CERTIFICATE) &&
	_hx509_Certificate_cmp(q->certificate, c) != 0)
	return 0;

    if ((q->match & HX509_QUERY_MATCH_SERIALNUMBER)
	&& der_heim_integer_cmp(&c->tbsCertificate.serialNumber, q->serial) != 0)
	return 0;

    if (q->match & HX509_QUERY_MATCH_ISSUER_NAME) {
	ret = _hx509_name_cmp(&c->tbsCertificate.issuer, q->issuer_name, &diff);
	if (ret || diff)
	    return 0;
    }

    if (q->match & HX509_QUERY_MATCH_SUBJECT_NAME) {
	ret = _hx509_name_cmp(&c->tbsCertificate.subject, q->subject_name, &diff);
	if (ret || diff)
	    return 0;
    }

    if (q->match & HX509_QUERY_MATCH_SUBJECT_KEY_ID) {
	SubjectKeyIdentifier si;

	ret = _hx509_find_extension_subject_key_id(c, &si);
	if (ret == 0) {
	    if (der_heim_octet_string_cmp(&si, q->subject_id) != 0)
		ret = 1;
	    free_SubjectKeyIdentifier(&si);
	}
	if (ret)
	    return 0;
    }
    if ((q->match & HX509_QUERY_MATCH_ISSUER_ID))
	return 0;
    if ((q->match & HX509_QUERY_PRIVATE_KEY) &&
	_hx509_cert_private_key(cert) == NULL)
	return 0;

    {
	unsigned ku = 0;
	if (q->match & HX509_QUERY_KU_DIGITALSIGNATURE)
	    ku |= (1 << 0);
	if (q->match & HX509_QUERY_KU_NONREPUDIATION)
	    ku |= (1 << 1);
	if (q->match & HX509_QUERY_KU_ENCIPHERMENT)
	    ku |= (1 << 2);
	if (q->match & HX509_QUERY_KU_DATAENCIPHERMENT)
	    ku |= (1 << 3);
	if (q->match & HX509_QUERY_KU_KEYAGREEMENT)
	    ku |= (1 << 4);
	if (q->match & HX509_QUERY_KU_KEYCERTSIGN)
	    ku |= (1 << 5);
	if (q->match & HX509_QUERY_KU_CRLSIGN)
	    ku |= (1 << 6);
	if (ku && check_key_usage(context, c, ku, TRUE))
	    return 0;
    }
    if ((q->match & HX509_QUERY_ANCHOR))
	return 0;

    if (q->match & HX509_QUERY_MATCH_LOCAL_KEY_ID) {
	hx509_cert_attribute a;

	a = hx509_cert_get_attribute(cert, &asn1_oid_id_pkcs_9_at_localKeyId);
	if (a == NULL)
	    return 0;
	if (der_heim_octet_string_cmp(&a->data, q->local_key_id) != 0)
	    return 0;
    }

    if (q->match & HX509_QUERY_NO_MATCH_PATH) {
	size_t i;

	for (i = 0; i < q->path->len; i++)
	    if (hx509_cert_cmp(q->path->val[i], cert) == 0)
		return 0;
    }
    if (q->match & HX509_QUERY_MATCH_FRIENDLY_NAME) {
	const char *name = hx509_cert_get_friendly_name(cert);
	if (name == NULL)
	    return 0;
	if (strcasecmp(q->friendlyname, name) != 0)
	    return 0;
    }
    if (q->match & HX509_QUERY_MATCH_FUNCTION) {
	ret = (*q->cmp_func)(context, cert, q->cmp_func_ctx);
	if (ret != 0)
	    return 0;
    }

    if (q->match & HX509_QUERY_MATCH_KEY_HASH_SHA1) {
	heim_octet_string os;

	os.data = c->tbsCertificate.subjectPublicKeyInfo.subjectPublicKey.data;
	os.length =
	    c->tbsCertificate.subjectPublicKeyInfo.subjectPublicKey.length / 8;

	ret = _hx509_verify_signature(context,
				      NULL,
				      hx509_signature_sha1(),
				      &os,
				      q->keyhash_sha1);
	if (ret != 0)
	    return 0;
    }

    if (q->match & HX509_QUERY_MATCH_TIME) {
	time_t t;
	t = _hx509_Time2time_t(&c->tbsCertificate.validity.notBefore);
	if (t > q->timenow)
	    return 0;
	t = _hx509_Time2time_t(&c->tbsCertificate.validity.notAfter);
	if (t < q->timenow)
	    return 0;
    }

    /* If an EKU is required, check the cert for it. */
    if ((q->match & HX509_QUERY_MATCH_EKU) &&
	hx509_cert_check_eku(context, cert, q->eku, 0))
	return 0;

    if ((q->match & HX509_QUERY_MATCH_EXPR)) {
	hx509_env env = NULL;

	ret = _hx509_cert_to_env(context, cert, &env);
	if (ret)
	    return 0;

	ret = _hx509_expr_eval(context, env, q->expr);
	hx509_env_free(&env);
	if (ret == 0)
	    return 0;
    }

    if (q->match & ~HX509_QUERY_MASK)
	return 0;

    return 1;
}