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
struct ocsp_fetch_options {char* url_path_string; int /*<<< orphan*/  pool_strings; int /*<<< orphan*/  nonce_flag; int /*<<< orphan*/  pass_strings; } ;
typedef  int /*<<< orphan*/  nonce ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  certs_strings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_1__*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_ocsp_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 

int
ocsp_fetch(struct ocsp_fetch_options *opt, int argc, char **argv)
{
    hx509_certs reqcerts, pool;
    heim_octet_string req, nonce_data, *nonce = &nonce_data;
    hx509_lock lock;
    int i, ret;
    char *file;
    const char *url = "/";

    memset(&nonce, 0, sizeof(nonce));

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    /* no nonce */
    if (!opt->nonce_flag)
	nonce = NULL;

    if (opt->url_path_string)
	url = opt->url_path_string;

    ret = hx509_certs_init(context, "MEMORY:ocsp-pool", 0, NULL, &pool);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    certs_strings(context, "ocsp-pool", pool, lock, &opt->pool_strings);

    file = argv[0];

    ret = hx509_certs_init(context, "MEMORY:ocsp-req", 0, NULL, &reqcerts);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    for (i = 1; i < argc; i++) {
	ret = hx509_certs_append(context, reqcerts, lock, argv[i]);
	if (ret)
	    errx(1, "hx509_certs_append: req: %s: %d", argv[i], ret);
    }

    ret = hx509_ocsp_request(context, reqcerts, pool, NULL, NULL, &req, nonce);
    if (ret)
	errx(1, "hx509_ocsp_request: req: %d", ret);

    {
	FILE *f;

	f = fopen(file, "w");
	if (f == NULL)
	    abort();

	fprintf(f,
		"POST %s HTTP/1.0\r\n"
		"Content-Type: application/ocsp-request\r\n"
		"Content-Length: %ld\r\n"
		"\r\n",
		url,
		(unsigned long)req.length);
	fwrite(req.data, req.length, 1, f);
	fclose(f);
    }

    if (nonce)
	der_free_octet_string(nonce);

    hx509_certs_free(&reqcerts);
    hx509_certs_free(&pool);

    return 0;
}