#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_4__ {int length; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 scalar_t__ errno ; 
 scalar_t__ krb5_ret_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ krb5_storage_get_eof_code (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_storage_read (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static krb5_error_code
ret_data_xdr(krb5_storage *sp, krb5_data *data)
{
    krb5_error_code ret;
    ret = krb5_ret_data(sp, data);
    if (ret)
	return ret;

    if ((data->length % 4) != 0) {
	char buf[4];
	size_t res;

	res = 4 - (data->length % 4);
	if (res != 4) {
	    ret = krb5_storage_read(sp, buf, res);
	    if((size_t)ret != res)
		return (ret < 0)? errno : krb5_storage_get_eof_code(sp);
	}
    }
    return 0;
}