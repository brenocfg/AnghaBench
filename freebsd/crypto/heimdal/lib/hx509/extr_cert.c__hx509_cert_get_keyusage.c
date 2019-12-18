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
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ extnValue; } ;
typedef  int /*<<< orphan*/  KeyUsage ;
typedef  TYPE_2__ Extension ;
typedef  int /*<<< orphan*/  Certificate ;

/* Variables and functions */
 int HX509_KU_CERT_MISSING ; 
 int _hx509_cert_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _hx509_get_cert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asn1_oid_id_x509_ce_keyUsage ; 
 int decode_KeyUsage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 TYPE_2__* find_extension (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
_hx509_cert_get_keyusage(hx509_context context,
			 hx509_cert c,
			 KeyUsage *ku)
{
    Certificate *cert;
    const Extension *e;
    size_t size;
    int ret;
    size_t i = 0;

    memset(ku, 0, sizeof(*ku));

    cert = _hx509_get_cert(c);

    if (_hx509_cert_get_version(cert) < 3)
	return 0;

    e = find_extension(cert, &asn1_oid_id_x509_ce_keyUsage, &i);
    if (e == NULL)
	return HX509_KU_CERT_MISSING;

    ret = decode_KeyUsage(e->extnValue.data, e->extnValue.length, ku, &size);
    if (ret)
	return ret;
    return 0;
}