#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct TYPE_6__ {TYPE_1__* certs; } ;
struct revoke_ocsp {int /*<<< orphan*/ * signer; int /*<<< orphan*/ * certs; TYPE_2__ ocsp; int /*<<< orphan*/  last_modfied; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/ * hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;
struct TYPE_5__ {size_t len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_2__ OCSPBasicOCSPResponse ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  free_OCSPBasicOCSPResponse (TYPE_2__*) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ *) ; 
 int hx509_cert_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int hx509_certs_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ **) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int parse_ocsp_basic (void*,size_t,TYPE_2__*) ; 
 int rk_undumpdata (int /*<<< orphan*/ ,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int
load_ocsp(hx509_context context, struct revoke_ocsp *ocsp)
{
    OCSPBasicOCSPResponse basic;
    hx509_certs certs = NULL;
    size_t length;
    struct stat sb;
    void *data;
    int ret;

    ret = rk_undumpdata(ocsp->path, &data, &length);
    if (ret)
	return ret;

    ret = stat(ocsp->path, &sb);
    if (ret)
	return errno;

    ret = parse_ocsp_basic(data, length, &basic);
    rk_xfree(data);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to parse OCSP response");
	return ret;
    }

    if (basic.certs) {
	size_t i;

	ret = hx509_certs_init(context, "MEMORY:ocsp-certs", 0,
			       NULL, &certs);
	if (ret) {
	    free_OCSPBasicOCSPResponse(&basic);
	    return ret;
	}

	for (i = 0; i < basic.certs->len; i++) {
	    hx509_cert c;

	    ret = hx509_cert_init(context, &basic.certs->val[i], &c);
	    if (ret)
		continue;

	    ret = hx509_certs_add(context, certs, c);
	    hx509_cert_free(c);
	    if (ret)
		continue;
	}
    }

    ocsp->last_modfied = sb.st_mtime;

    free_OCSPBasicOCSPResponse(&ocsp->ocsp);
    hx509_certs_free(&ocsp->certs);
    hx509_cert_free(ocsp->signer);

    ocsp->ocsp = basic;
    ocsp->certs = certs;
    ocsp->signer = NULL;

    return 0;
}