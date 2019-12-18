#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct ks_pkcs12 {scalar_t__ certs; struct ks_pkcs12* fn; } ;
struct hx509_collector {int dummy; } ;
typedef  int /*<<< orphan*/ * hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
struct TYPE_18__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ heim_octet_string ;
struct TYPE_20__ {size_t len; TYPE_4__* val; } ;
struct TYPE_15__ {TYPE_1__* content; int /*<<< orphan*/  contentType; } ;
struct TYPE_19__ {TYPE_2__ authSafe; } ;
struct TYPE_17__ {TYPE_3__* content; int /*<<< orphan*/  contentType; } ;
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ PKCS12_PFX ;
typedef  TYPE_7__ PKCS12_AuthenticatedSafe ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int HX509_CERTS_CREATE ; 
 int _hx509_collector_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hx509_collector**) ; 
 int _hx509_collector_collect_certs (int /*<<< orphan*/ ,struct hx509_collector*,scalar_t__*) ; 
 int /*<<< orphan*/  _hx509_collector_free (struct hx509_collector*) ; 
 int /*<<< orphan*/ * _hx509_empty_lock ; 
 int /*<<< orphan*/  asn1_oid_id_pkcs7_data ; 
 struct ks_pkcs12* calloc (int,int) ; 
 int decode_PKCS12_AuthenticatedSafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int decode_PKCS12_OctetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int decode_PKCS12_PFX (void*,size_t,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_octet_string (TYPE_5__*) ; 
 scalar_t__ der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ks_pkcs12*) ; 
 int /*<<< orphan*/  free_PKCS12_AuthenticatedSafe (TYPE_7__*) ; 
 int /*<<< orphan*/  free_PKCS12_PFX (TYPE_6__*) ; 
 int /*<<< orphan*/  hx509_certs_free (scalar_t__*) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  parse_pkcs12_type (int /*<<< orphan*/ ,struct hx509_collector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rk_undumpdata (char const*,void**,size_t*) ; 
 int /*<<< orphan*/  rk_xfree (void*) ; 
 struct ks_pkcs12* strdup (char const*) ; 

__attribute__((used)) static int
p12_init(hx509_context context,
	 hx509_certs certs, void **data, int flags,
	 const char *residue, hx509_lock lock)
{
    struct ks_pkcs12 *p12;
    size_t len;
    void *buf;
    PKCS12_PFX pfx;
    PKCS12_AuthenticatedSafe as;
    int ret;
    size_t i;
    struct hx509_collector *c;

    *data = NULL;

    if (lock == NULL)
	lock = _hx509_empty_lock;

    ret = _hx509_collector_alloc(context, lock, &c);
    if (ret)
	return ret;

    p12 = calloc(1, sizeof(*p12));
    if (p12 == NULL) {
	ret = ENOMEM;
	hx509_set_error_string(context, 0, ret, "out of memory");
	goto out;
    }

    p12->fn = strdup(residue);
    if (p12->fn == NULL) {
	ret = ENOMEM;
	hx509_set_error_string(context, 0, ret, "out of memory");
	goto out;
    }

    if (flags & HX509_CERTS_CREATE) {
	ret = hx509_certs_init(context, "MEMORY:ks-file-create",
			       0, lock, &p12->certs);
	if (ret == 0)
	    *data = p12;
	goto out;
    }

    ret = rk_undumpdata(residue, &buf, &len);
    if (ret) {
	hx509_clear_error_string(context);
	goto out;
    }

    ret = decode_PKCS12_PFX(buf, len, &pfx, NULL);
    rk_xfree(buf);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to decode the PFX in %s", residue);
	goto out;
    }

    if (der_heim_oid_cmp(&pfx.authSafe.contentType, &asn1_oid_id_pkcs7_data) != 0) {
	free_PKCS12_PFX(&pfx);
	ret = EINVAL;
	hx509_set_error_string(context, 0, ret,
			       "PKCS PFX isn't a pkcs7-data container");
	goto out;
    }

    if (pfx.authSafe.content == NULL) {
	free_PKCS12_PFX(&pfx);
	ret = EINVAL;
	hx509_set_error_string(context, 0, ret,
			       "PKCS PFX missing data");
	goto out;
    }

    {
	heim_octet_string asdata;

	ret = decode_PKCS12_OctetString(pfx.authSafe.content->data,
					pfx.authSafe.content->length,
					&asdata,
					NULL);
	free_PKCS12_PFX(&pfx);
	if (ret) {
	    hx509_clear_error_string(context);
	    goto out;
	}
	ret = decode_PKCS12_AuthenticatedSafe(asdata.data,
					      asdata.length,
					      &as,
					      NULL);
	der_free_octet_string(&asdata);
	if (ret) {
	    hx509_clear_error_string(context);
	    goto out;
	}
    }

    for (i = 0; i < as.len; i++)
	parse_pkcs12_type(context,
			  c,
			  &as.val[i].contentType,
			  as.val[i].content->data,
			  as.val[i].content->length,
			  NULL);

    free_PKCS12_AuthenticatedSafe(&as);

    ret = _hx509_collector_collect_certs(context, c, &p12->certs);
    if (ret == 0)
	*data = p12;

out:
    _hx509_collector_free(c);

    if (ret && p12) {
	if (p12->fn)
	    free(p12->fn);
	if (p12->certs)
	    hx509_certs_free(&p12->certs);
	free(p12);
    }

    return ret;
}