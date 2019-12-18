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
typedef  int /*<<< orphan*/  hx509_request ;
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_5__ {int /*<<< orphan*/  subject; int /*<<< orphan*/  subjectPKInfo; } ;
struct TYPE_6__ {TYPE_1__ certificationRequestInfo; } ;
typedef  TYPE_1__ CertificationRequestInfo ;
typedef  TYPE_2__ CertificationRequest ;

/* Variables and functions */
 int HX509_UNSUPPORTED_OPERATION ; 
 int _hx509_name_from_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_CertificationRequest (void*,size_t,TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  free_CertificationRequest (TYPE_2__*) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_request_free (int /*<<< orphan*/ *) ; 
 int hx509_request_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_request_set_SubjectPublicKeyInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_request_set_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int rk_undumpdata (char const*,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int
_hx509_request_parse(hx509_context context,
		     const char *path,
		     hx509_request *req)
{
    CertificationRequest r;
    CertificationRequestInfo *rinfo;
    hx509_name subject;
    size_t len, size;
    void *p;
    int ret;

    if (strncmp(path, "PKCS10:", 7) != 0) {
	hx509_set_error_string(context, 0, HX509_UNSUPPORTED_OPERATION,
			       "unsupport type in %s", path);
	return HX509_UNSUPPORTED_OPERATION;
    }
    path += 7;

    /* XXX PEM request */

    ret = rk_undumpdata(path, &p, &len);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Failed to map file %s", path);
	return ret;
    }

    ret = decode_CertificationRequest(p, len, &r, &size);
    rk_xfree(p);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "Failed to decode %s", path);
	return ret;
    }

    ret = hx509_request_init(context, req);
    if (ret) {
	free_CertificationRequest(&r);
	return ret;
    }

    rinfo = &r.certificationRequestInfo;

    ret = hx509_request_set_SubjectPublicKeyInfo(context, *req,
						  &rinfo->subjectPKInfo);
    if (ret) {
	free_CertificationRequest(&r);
	hx509_request_free(req);
	return ret;
    }

    ret = _hx509_name_from_Name(&rinfo->subject, &subject);
    if (ret) {
	free_CertificationRequest(&r);
	hx509_request_free(req);
	return ret;
    }
    ret = hx509_request_set_name(context, *req, subject);
    hx509_name_free(&subject);
    free_CertificationRequest(&r);
    if (ret) {
	hx509_request_free(req);
	return ret;
    }

    return 0;
}