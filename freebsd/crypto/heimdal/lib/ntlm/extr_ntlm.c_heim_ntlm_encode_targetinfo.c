#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntlm_targetinfo {int /*<<< orphan*/  avflags; int /*<<< orphan*/  dnstreename; int /*<<< orphan*/  dnsdomainname; int /*<<< orphan*/  dnsservername; int /*<<< orphan*/  domainname; int /*<<< orphan*/  servername; } ;
struct ntlm_buf {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KRB5_STORAGE_BYTEORDER_LE ; 
 int /*<<< orphan*/  encode_ti_string (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_set_byteorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_store_int16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_uint16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
heim_ntlm_encode_targetinfo(const struct ntlm_targetinfo *ti,
			    int ucs2,
			    struct ntlm_buf *data)
{
    krb5_error_code ret;
    krb5_storage *out;

    data->data = NULL;
    data->length = 0;

    out = krb5_storage_emem();
    if (out == NULL)
	return ENOMEM;

    krb5_storage_set_byteorder(out, KRB5_STORAGE_BYTEORDER_LE);

    if (ti->servername)
	CHECK(encode_ti_string(out, 1, ucs2, ti->servername), 0);
    if (ti->domainname)
	CHECK(encode_ti_string(out, 2, ucs2, ti->domainname), 0);
    if (ti->dnsservername)
	CHECK(encode_ti_string(out, 3, ucs2, ti->dnsservername), 0);
    if (ti->dnsdomainname)
	CHECK(encode_ti_string(out, 4, ucs2, ti->dnsdomainname), 0);
    if (ti->dnstreename)
	CHECK(encode_ti_string(out, 5, ucs2, ti->dnstreename), 0);
    if (ti->avflags) {
	CHECK(krb5_store_uint16(out, 6), 0);
	CHECK(krb5_store_uint16(out, 4), 0);
	CHECK(krb5_store_uint32(out, ti->avflags), 0);
    }

    /* end tag */
    CHECK(krb5_store_int16(out, 0), 0);
    CHECK(krb5_store_int16(out, 0), 0);

    {
	krb5_data d;
	ret = krb5_storage_to_data(out, &d);
	data->data = d.data;
	data->length = d.length;
    }
out:
    krb5_storage_free(out);
    return ret;
}