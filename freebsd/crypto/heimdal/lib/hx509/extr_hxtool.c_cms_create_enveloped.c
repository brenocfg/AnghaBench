#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cms_envelope_options {int encryption_type_string; scalar_t__ content_info_flag; int /*<<< orphan*/  content_type_string; scalar_t__ allow_weak_crypto_flag; int /*<<< orphan*/  certificate_strings; int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  contentType ;

/* Variables and functions */
 int HX509_CMS_EV_ALLOW_WEAK ; 
 int /*<<< orphan*/  HX509_QUERY_OPTION_KU_ENCIPHERMENT ; 
 int _hx509_write_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_data ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_envelopedData ; 
 int /*<<< orphan*/  certs_strings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 
 int hx509_certs_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_cms_envelope_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int hx509_cms_wrap_ContentInfo (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * hx509_crypto_enctype_by_name (int) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_query_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_query_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_query_match_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rk_undumpdata (char*,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 

int
cms_create_enveloped(struct cms_envelope_options *opt, int argc, char **argv)
{
    heim_oid contentType;
    heim_octet_string o;
    const heim_oid *enctype = NULL;
    hx509_query *q;
    hx509_certs certs;
    hx509_cert cert;
    int ret;
    size_t sz;
    void *p;
    hx509_lock lock;
    int flags = 0;

    memset(&contentType, 0, sizeof(contentType));

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = rk_undumpdata(argv[0], &p, &sz);
    if (ret)
	err(1, "map_file: %s: %d", argv[0], ret);

    ret = hx509_certs_init(context, "MEMORY:cert-store", 0, NULL, &certs);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    certs_strings(context, "store", certs, lock, &opt->certificate_strings);

    if (opt->allow_weak_crypto_flag)
	flags |= HX509_CMS_EV_ALLOW_WEAK;

    if (opt->encryption_type_string) {
	enctype = hx509_crypto_enctype_by_name(opt->encryption_type_string);
	if (enctype == NULL)
	    errx(1, "encryption type: %s no found",
		 opt->encryption_type_string);
    }

    ret = hx509_query_alloc(context, &q);
    if (ret)
	errx(1, "hx509_query_alloc: %d", ret);

    hx509_query_match_option(q, HX509_QUERY_OPTION_KU_ENCIPHERMENT);

    ret = hx509_certs_find(context, certs, q, &cert);
    hx509_query_free(context, q);
    if (ret)
	errx(1, "hx509_certs_find: %d", ret);

    parse_oid(opt->content_type_string, &asn1_oid_id_pkcs7_data, &contentType);

    ret = hx509_cms_envelope_1(context, flags, cert, p, sz, enctype,
			       &contentType, &o);
    if (ret)
	errx(1, "hx509_cms_envelope_1: %d", ret);

    hx509_cert_free(cert);
    hx509_certs_free(&certs);
    rk_xfree(p);
    der_free_oid(&contentType);

    if (opt->content_info_flag) {
	heim_octet_string wo;

	ret = hx509_cms_wrap_ContentInfo(&asn1_oid_id_pkcs7_envelopedData, &o, &wo);
	if (ret)
	    errx(1, "hx509_cms_wrap_ContentInfo: %d", ret);

	der_free_octet_string(&o);
	o = wo;
    }

    hx509_lock_free(lock);

    ret = _hx509_write_file(argv[1], o.data, o.length);
    if (ret)
	errx(1, "hx509_write_file: %d", ret);

    der_free_octet_string(&o);

    return 0;
}