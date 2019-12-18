#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
struct ntlm_targetinfo {int /*<<< orphan*/  avflags; int /*<<< orphan*/  dnstreename; int /*<<< orphan*/  dnsdomainname; int /*<<< orphan*/  dnsservername; int /*<<< orphan*/  domainname; int /*<<< orphan*/  servername; } ;
struct ntlm_buf {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  krb5_storage ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KRB5_STORAGE_BYTEORDER_LE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  krb5_ret_uint16 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_readonly_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_storage_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_set_byteorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ntlm_targetinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ret_string (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

int
heim_ntlm_decode_targetinfo(const struct ntlm_buf *data,
			    int ucs2,
			    struct ntlm_targetinfo *ti)
{
    uint16_t type, len;
    krb5_storage *in;
    int ret = 0, done = 0;

    memset(ti, 0, sizeof(*ti));

    if (data->length == 0)
	return 0;

    in = krb5_storage_from_readonly_mem(data->data, data->length);
    if (in == NULL)
	return ENOMEM;
    krb5_storage_set_byteorder(in, KRB5_STORAGE_BYTEORDER_LE);

    while (!done) {
	CHECK(krb5_ret_uint16(in, &type), 0);
	CHECK(krb5_ret_uint16(in, &len), 0);

	switch (type) {
	case 0:
	    done = 1;
	    break;
	case 1:
	    CHECK(ret_string(in, ucs2, len, &ti->servername), 0);
	    break;
	case 2:
	    CHECK(ret_string(in, ucs2, len, &ti->domainname), 0);
	    break;
	case 3:
	    CHECK(ret_string(in, ucs2, len, &ti->dnsservername), 0);
	    break;
	case 4:
	    CHECK(ret_string(in, ucs2, len, &ti->dnsdomainname), 0);
	    break;
	case 5:
	    CHECK(ret_string(in, ucs2, len, &ti->dnstreename), 0);
	    break;
	case 6:
	    CHECK(krb5_ret_uint32(in, &ti->avflags), 0);
	    break;
	default:
	    krb5_storage_seek(in, len, SEEK_CUR);
	    break;
	}
    }
 out:
    if (in)
	krb5_storage_free(in);
    return ret;
}