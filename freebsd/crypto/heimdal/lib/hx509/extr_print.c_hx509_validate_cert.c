#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct cert_status {int selfsigned; int /*<<< orphan*/  haveCRLDP; scalar_t__ haveSAN; scalar_t__ haveIAN; scalar_t__ isproxy; scalar_t__ isca; int /*<<< orphan*/  haveSKI; int /*<<< orphan*/  haveAKI; } ;
typedef  int /*<<< orphan*/  status ;
typedef  TYPE_3__* hx509_validate_ctx ;
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_20__ {int /*<<< orphan*/  extnID; scalar_t__ critical; } ;
struct TYPE_15__ {int /*<<< orphan*/  notAfter; int /*<<< orphan*/  notBefore; } ;
struct TYPE_18__ {int* version; int /*<<< orphan*/  _save; TYPE_2__* extensions; TYPE_1__ validity; } ;
struct TYPE_19__ {int /*<<< orphan*/  signatureValue; TYPE_4__ tbsCertificate; int /*<<< orphan*/  signatureAlgorithm; } ;
struct TYPE_17__ {int flags; } ;
struct TYPE_16__ {size_t len; TYPE_8__* val; } ;
struct TYPE_14__ {int /*<<< orphan*/  cf; int /*<<< orphan*/  (* func ) (TYPE_3__*,struct cert_status*,int /*<<< orphan*/ ,TYPE_8__*) ;int /*<<< orphan*/ * name; int /*<<< orphan*/  oid; } ;
typedef  TYPE_4__ TBSCertificate ;
typedef  TYPE_5__ Certificate ;

/* Variables and functions */
 int HX509_VALIDATE_F_VALIDATE ; 
 int HX509_VALIDATE_F_VERBOSE ; 
 int /*<<< orphan*/  Time2string (int /*<<< orphan*/ *,char**) ; 
 int _hx509_cert_get_version (TYPE_5__*) ; 
 TYPE_5__* _hx509_get_cert (int /*<<< orphan*/ ) ; 
 int _hx509_verify_signature_bitstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_11__* check_extension ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hx509_cert_get_issuer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_cert_get_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hx509_name_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 scalar_t__ hx509_name_is_null_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_name_to_string (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  hx509_oid_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (struct cert_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct cert_status*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  validate_print (TYPE_3__*,int,char*,...) ; 
 int /*<<< orphan*/  validate_vprint ; 

int
hx509_validate_cert(hx509_context context,
		    hx509_validate_ctx ctx,
		    hx509_cert cert)
{
    Certificate *c = _hx509_get_cert(cert);
    TBSCertificate *t = &c->tbsCertificate;
    hx509_name issuer, subject;
    char *str;
    struct cert_status status;
    int ret;

    memset(&status, 0, sizeof(status));

    if (_hx509_cert_get_version(c) != 3)
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		       "Not version 3 certificate\n");

    if ((t->version == NULL || *t->version < 2) && t->extensions)
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Not version 3 certificate with extensions\n");

    if (_hx509_cert_get_version(c) >= 3 && t->extensions == NULL)
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Version 3 certificate without extensions\n");

    ret = hx509_cert_get_subject(cert, &subject);
    if (ret) abort();
    hx509_name_to_string(subject, &str);
    validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		   "subject name: %s\n", str);
    free(str);

    ret = hx509_cert_get_issuer(cert, &issuer);
    if (ret) abort();
    hx509_name_to_string(issuer, &str);
    validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		   "issuer name: %s\n", str);
    free(str);

    if (hx509_name_cmp(subject, issuer) == 0) {
	status.selfsigned = 1;
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		       "\tis a self-signed certificate\n");
    }

    validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
		   "Validity:\n");

    Time2string(&t->validity.notBefore, &str);
    validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "\tnotBefore %s\n", str);
    free(str);
    Time2string(&t->validity.notAfter, &str);
    validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "\tnotAfter  %s\n", str);
    free(str);

    if (t->extensions) {
	size_t i, j;

	if (t->extensions->len == 0) {
	    validate_print(ctx,
			   HX509_VALIDATE_F_VALIDATE|HX509_VALIDATE_F_VERBOSE,
			   "The empty extensions list is not "
			   "allowed by PKIX\n");
	}

	for (i = 0; i < t->extensions->len; i++) {

	    for (j = 0; check_extension[j].name; j++)
		if (der_heim_oid_cmp(check_extension[j].oid,
				     &t->extensions->val[i].extnID) == 0)
		    break;
	    if (check_extension[j].name == NULL) {
		int flags = HX509_VALIDATE_F_VERBOSE;
		if (t->extensions->val[i].critical)
		    flags |= HX509_VALIDATE_F_VALIDATE;
		validate_print(ctx, flags, "don't know what ");
		if (t->extensions->val[i].critical)
		    validate_print(ctx, flags, "and is CRITICAL ");
		if (ctx->flags & flags)
		    hx509_oid_print(&t->extensions->val[i].extnID,
				    validate_vprint, ctx);
		validate_print(ctx, flags, " is\n");
		continue;
	    }
	    validate_print(ctx,
			   HX509_VALIDATE_F_VALIDATE|HX509_VALIDATE_F_VERBOSE,
			   "checking extention: %s\n",
			   check_extension[j].name);
	    (*check_extension[j].func)(ctx,
				       &status,
				       check_extension[j].cf,
				       &t->extensions->val[i]);
	}
    } else
	validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "no extentions\n");

    if (status.isca) {
	if (!status.haveSKI)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "CA certificate have no SubjectKeyIdentifier\n");

    } else {
	if (!status.haveAKI)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "Is not CA and doesn't have "
			   "AuthorityKeyIdentifier\n");
    }


    if (!status.haveSKI)
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Doesn't have SubjectKeyIdentifier\n");

    if (status.isproxy && status.isca)
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Proxy and CA at the same time!\n");

    if (status.isproxy) {
	if (status.haveSAN)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "Proxy and have SAN\n");
	if (status.haveIAN)
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "Proxy and have IAN\n");
    }

    if (hx509_name_is_null_p(subject) && !status.haveSAN)
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "NULL subject DN and doesn't have a SAN\n");

    if (!status.selfsigned && !status.haveCRLDP)
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Not a CA nor PROXY and doesn't have"
		       "CRL Dist Point\n");

    if (status.selfsigned) {
	ret = _hx509_verify_signature_bitstring(context,
						cert,
						&c->signatureAlgorithm,
						&c->tbsCertificate._save,
						&c->signatureValue);
	if (ret == 0)
	    validate_print(ctx, HX509_VALIDATE_F_VERBOSE,
			   "Self-signed certificate was self-signed\n");
	else
	    validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
			   "Self-signed certificate NOT really self-signed!\n");
    }

    hx509_name_free(&subject);
    hx509_name_free(&issuer);

    return 0;
}