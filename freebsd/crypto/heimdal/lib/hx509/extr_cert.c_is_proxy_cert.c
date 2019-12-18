#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ extnValue; } ;
typedef  int /*<<< orphan*/  ProxyCertInfo ;
typedef  TYPE_2__ Extension ;
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int HX509_EXTENSION_NOT_FOUND ; 
 int HX509_EXTRA_DATA_AFTER_STRUCTURE ; 
 int /*<<< orphan*/  asn1_oid_id_pkix_pe_proxyCertInfo ; 
 int decode_ProxyCertInfo (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t*) ; 
 TYPE_2__* find_extension (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_ProxyCertInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
is_proxy_cert(hx509_context context,
	      const Certificate *cert,
	      ProxyCertInfo *rinfo)
{
    ProxyCertInfo info;
    const Extension *e;
    size_t size;
    int ret;
    size_t i = 0;

    if (rinfo)
	memset(rinfo, 0, sizeof(*rinfo));

    e = find_extension(cert, &asn1_oid_id_pkix_pe_proxyCertInfo, &i);
    if (e == NULL) {
	hx509_clear_error_string(context);
	return HX509_EXTENSION_NOT_FOUND;
    }

    ret = decode_ProxyCertInfo(e->extnValue.data,
			       e->extnValue.length,
			       &info,
			       &size);
    if (ret) {
	hx509_clear_error_string(context);
	return ret;
    }
    if (size != e->extnValue.length) {
	free_ProxyCertInfo(&info);
	hx509_clear_error_string(context);
	return HX509_EXTRA_DATA_AFTER_STRUCTURE;
    }
    if (rinfo == NULL)
	free_ProxyCertInfo(&info);
    else
	*rinfo = info;

    return 0;
}