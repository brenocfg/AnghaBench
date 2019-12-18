#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ num_strings; } ;
struct TYPE_10__ {scalar_t__ num_strings; } ;
struct cms_create_sd_options {scalar_t__ detached_signature_flag; scalar_t__ pem_flag; scalar_t__ content_info_flag; int /*<<< orphan*/  content_type_string; TYPE_2__ peer_alg_strings; scalar_t__ embed_leaf_only_flag; int /*<<< orphan*/  embedded_certs_flag; int /*<<< orphan*/  signer_string; scalar_t__ signer_flag; scalar_t__ id_by_name_flag; TYPE_7__ anchors_strings; TYPE_7__ pool_strings; TYPE_7__ certificate_strings; int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_pem_header ;
typedef  int /*<<< orphan*/ * hx509_peer_info ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/ * hx509_certs ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  contentType ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HX509_CMS_SIGNATURE_DETACHED ; 
 int HX509_CMS_SIGNATURE_ID_NAME ; 
 int HX509_CMS_SIGNATURE_LEAF_ONLY ; 
 int HX509_CMS_SIGNATURE_NO_CERTS ; 
 int HX509_CMS_SIGNATURE_NO_SIGNER ; 
 int /*<<< orphan*/  HX509_QUERY_OPTION_KU_DIGITALSIGNATURE ; 
 int /*<<< orphan*/  HX509_QUERY_OPTION_PRIVATE_KEY ; 
 int _hx509_write_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_data ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_signedData ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  certs_strings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int hx509_certs_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_cms_create_signed (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int hx509_cms_wrap_ContentInfo (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*,...) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_peer_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_pem_add_header (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  hx509_pem_free_header (int /*<<< orphan*/ *) ; 
 int hx509_pem_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hx509_query_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_query_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_query_match_friendly_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_query_match_option (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  print_signer ; 
 int rk_undumpdata (char*,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 

int
cms_create_sd(struct cms_create_sd_options *opt, int argc, char **argv)
{
    heim_oid contentType;
    hx509_peer_info peer = NULL;
    heim_octet_string o;
    hx509_query *q;
    hx509_lock lock;
    hx509_certs store, pool, anchors, signer = NULL;
    size_t sz;
    void *p;
    int ret, flags = 0;
    char *infile, *outfile = NULL;

    memset(&contentType, 0, sizeof(contentType));

    infile = argv[0];

    if (argc < 2) {
	asprintf(&outfile, "%s.%s", infile,
		 opt->pem_flag ? "pem" : "cms-signeddata");
	if (outfile == NULL)
	    errx(1, "out of memory");
    } else
	outfile = argv[1];

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = hx509_certs_init(context, "MEMORY:cert-store", 0, NULL, &store);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");
    ret = hx509_certs_init(context, "MEMORY:cert-pool", 0, NULL, &pool);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    certs_strings(context, "store", store, lock, &opt->certificate_strings);
    certs_strings(context, "pool", pool, lock, &opt->pool_strings);

    if (opt->anchors_strings.num_strings) {
	ret = hx509_certs_init(context, "MEMORY:cert-anchors",
			       0, NULL, &anchors);
	if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");
	certs_strings(context, "anchors", anchors, lock, &opt->anchors_strings);
    } else
	anchors = NULL;

    if (opt->detached_signature_flag)
	flags |= HX509_CMS_SIGNATURE_DETACHED;
    if (opt->id_by_name_flag)
	flags |= HX509_CMS_SIGNATURE_ID_NAME;
    if (!opt->signer_flag) {
	flags |= HX509_CMS_SIGNATURE_NO_SIGNER;

    }

    if (opt->signer_flag) {
	ret = hx509_query_alloc(context, &q);
	if (ret)
	    errx(1, "hx509_query_alloc: %d", ret);

	hx509_query_match_option(q, HX509_QUERY_OPTION_PRIVATE_KEY);
	hx509_query_match_option(q, HX509_QUERY_OPTION_KU_DIGITALSIGNATURE);

	if (opt->signer_string)
	    hx509_query_match_friendly_name(q, opt->signer_string);

	ret = hx509_certs_filter(context, store, q, &signer);
	hx509_query_free(context, q);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_certs_find");
    }
    if (!opt->embedded_certs_flag)
	flags |= HX509_CMS_SIGNATURE_NO_CERTS;
    if (opt->embed_leaf_only_flag)
	flags |= HX509_CMS_SIGNATURE_LEAF_ONLY;

    ret = rk_undumpdata(infile, &p, &sz);
    if (ret)
	err(1, "map_file: %s: %d", infile, ret);

    if (opt->peer_alg_strings.num_strings)
	peer_strings(context, &peer, &opt->peer_alg_strings);

    parse_oid(opt->content_type_string, &asn1_oid_id_pkcs7_data, &contentType);

    ret = hx509_cms_create_signed(context,
				  flags,
				  &contentType,
				  p,
				  sz,
				  NULL,
				  signer,
				  peer,
				  anchors,
				  pool,
				  &o);
    if (ret)
	hx509_err(context, 1, ret, "hx509_cms_create_signed: %d", ret);

    hx509_certs_free(&anchors);
    hx509_certs_free(&pool);
    hx509_certs_free(&store);
    rk_xfree(p);
    hx509_lock_free(lock);
    hx509_peer_info_free(peer);
    der_free_oid(&contentType);

    if (opt->content_info_flag) {
	heim_octet_string wo;

	ret = hx509_cms_wrap_ContentInfo(&asn1_oid_id_pkcs7_signedData, &o, &wo);
	if (ret)
	    errx(1, "hx509_cms_wrap_ContentInfo: %d", ret);

	der_free_octet_string(&o);
	o = wo;
    }

    if (opt->pem_flag) {
	hx509_pem_header *header = NULL;
	FILE *f;

	hx509_pem_add_header(&header, "Content-disposition",
			     opt->detached_signature_flag ?
			     "detached" : "inline");
	if (signer) {
	    ret = hx509_certs_iter_f(context, signer, print_signer, header);
	    if (ret)
		hx509_err(context, 1, ret, "print signer");
	}

	f = fopen(outfile, "w");
	if (f == NULL)
	    err(1, "open %s", outfile);

	ret = hx509_pem_write(context, "CMS SIGNEDDATA", header, f,
			      o.data, o.length);
	fclose(f);
	hx509_pem_free_header(header);
	if (ret)
	    errx(1, "hx509_pem_write: %d", ret);

    } else {
	ret = _hx509_write_file(outfile, o.data, o.length);
	if (ret)
	    errx(1, "hx509_write_file: %d", ret);
    }

    hx509_certs_free(&signer);
    free(o.data);

    return 0;
}