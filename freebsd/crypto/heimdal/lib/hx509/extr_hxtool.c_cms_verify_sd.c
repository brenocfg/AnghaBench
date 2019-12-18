#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pem_data {scalar_t__ detached_data; TYPE_1__* os; } ;
struct cms_verify_sd_options {char* signed_content_string; scalar_t__ allow_wrong_oid_flag; int /*<<< orphan*/  signer_allowed_flag; scalar_t__ content_info_flag; scalar_t__ pem_flag; int /*<<< orphan*/  certificate_strings; int /*<<< orphan*/  anchors_strings; int /*<<< orphan*/  pass_strings; scalar_t__ missing_revoke_flag; } ;
typedef  int /*<<< orphan*/ * hx509_verify_ctx ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/ * hx509_certs ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_9__ {void* data; size_t length; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HX509_CMS_VS_ALLOW_DATA_OID_MISMATCH ; 
 int HX509_CMS_VS_ALLOW_ZERO_SIGNER ; 
 int _hx509_map_file_os (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_unmap_file_os (TYPE_1__*) ; 
 int _hx509_write_file (char*,void*,size_t) ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_signedData ; 
 int /*<<< orphan*/  certs_strings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_print_heim_oid (int /*<<< orphan*/ *,char,char**) ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_ci_print_names ; 
 int hx509_cms_unwrap_ContentInfo (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int hx509_cms_verify_signed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void*,size_t,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_context_set_missing_revoke (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_pem_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pem_data*) ; 
 int /*<<< orphan*/  hx509_verify_attach_anchors (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_verify_destroy_ctx (int /*<<< orphan*/ *) ; 
 int hx509_verify_init_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pem_reader ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rk_undumpdata (char*,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 

int
cms_verify_sd(struct cms_verify_sd_options *opt, int argc, char **argv)
{
    hx509_verify_ctx ctx = NULL;
    heim_oid type;
    heim_octet_string c, co, signeddata, *sd = NULL;
    hx509_certs store = NULL;
    hx509_certs signers = NULL;
    hx509_certs anchors = NULL;
    hx509_lock lock;
    int ret, flags = 0;

    size_t sz;
    void *p = NULL;

    if (opt->missing_revoke_flag)
	hx509_context_set_missing_revoke(context, 1);

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = hx509_verify_init_ctx(context, &ctx);
    if (ret)
	hx509_err(context, 1, ret, "hx509_verify_init_ctx");

    ret = hx509_certs_init(context, "MEMORY:cms-anchors", 0, NULL, &anchors);
    if (ret)
	hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");
    ret = hx509_certs_init(context, "MEMORY:cert-store", 0, NULL, &store);
    if (ret)
	hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    certs_strings(context, "anchors", anchors, lock, &opt->anchors_strings);
    certs_strings(context, "store", store, lock, &opt->certificate_strings);

    if (opt->pem_flag) {
	struct pem_data pd;
	FILE *f;

	pd.os = &co;
	pd.detached_data = 0;

	f = fopen(argv[0], "r");
	if (f == NULL)
	    err(1, "Failed to open file %s", argv[0]);

	ret = hx509_pem_read(context, f, pem_reader, &pd);
	fclose(f);
	if (ret)
	    errx(1, "PEM reader failed: %d", ret);

	if (pd.detached_data && opt->signed_content_string == NULL) {
	    char *r = strrchr(argv[0], '.');
	    if (r && strcasecmp(r, ".pem") == 0) {
		char *s = strdup(argv[0]);
		if (s == NULL)
		    errx(1, "malloc: out of memory");
		s[r - argv[0]] = '\0';
		ret = _hx509_map_file_os(s, &signeddata);
		if (ret)
		    errx(1, "map_file: %s: %d", s, ret);
		free(s);
		sd = &signeddata;
	    }
	}

    } else {
	ret = rk_undumpdata(argv[0], &p, &sz);
	if (ret)
	    err(1, "map_file: %s: %d", argv[0], ret);

	co.data = p;
	co.length = sz;
    }

    if (opt->signed_content_string) {
	ret = _hx509_map_file_os(opt->signed_content_string, &signeddata);
	if (ret)
	    errx(1, "map_file: %s: %d", opt->signed_content_string, ret);
	sd = &signeddata;
    }

    if (opt->content_info_flag) {
	heim_octet_string uwco;
	heim_oid oid;

	ret = hx509_cms_unwrap_ContentInfo(&co, &oid, &uwco, NULL);
	if (ret)
	    errx(1, "hx509_cms_unwrap_ContentInfo: %d", ret);

	if (der_heim_oid_cmp(&oid, &asn1_oid_id_pkcs7_signedData) != 0)
	    errx(1, "Content is not SignedData");
	der_free_oid(&oid);

	if (p == NULL)
	    der_free_octet_string(&co);
	else {
	    rk_xfree(p);
	    p = NULL;
	}
	co = uwco;
    }

    hx509_verify_attach_anchors(ctx, anchors);

    if (!opt->signer_allowed_flag)
	flags |= HX509_CMS_VS_ALLOW_ZERO_SIGNER;
    if (opt->allow_wrong_oid_flag)
	flags |= HX509_CMS_VS_ALLOW_DATA_OID_MISMATCH;

    ret = hx509_cms_verify_signed(context, ctx, flags, co.data, co.length, sd,
				  store, &type, &c, &signers);
    if (p != co.data)
	der_free_octet_string(&co);
    else
	rk_xfree(p);
    if (ret)
	hx509_err(context, 1, ret, "hx509_cms_verify_signed");

    {
	char *str;
	der_print_heim_oid(&type, '.', &str);
	printf("type: %s\n", str);
	free(str);
	der_free_oid(&type);
    }
    if (signers == NULL) {
	printf("unsigned\n");
    } else {
	printf("signers:\n");
	hx509_certs_iter_f(context, signers, hx509_ci_print_names, stdout);
    }

    hx509_verify_destroy_ctx(ctx);

    hx509_certs_free(&store);
    hx509_certs_free(&signers);
    hx509_certs_free(&anchors);

    hx509_lock_free(lock);

    if (argc > 1) {
	ret = _hx509_write_file(argv[1], c.data, c.length);
	if (ret)
	    errx(1, "hx509_write_file: %d", ret);
    }

    der_free_octet_string(&c);

    if (sd)
	_hx509_unmap_file_os(sd);

    return 0;
}