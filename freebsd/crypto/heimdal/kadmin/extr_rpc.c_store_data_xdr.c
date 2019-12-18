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
 scalar_t__ krb5_storage_get_eof_code (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_storage_write (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ krb5_store_data (int /*<<< orphan*/ *,TYPE_1__) ; 

__attribute__((used)) static krb5_error_code
store_data_xdr(krb5_storage *sp, krb5_data data)
{
    krb5_error_code ret;
    size_t res;

    ret = krb5_store_data(sp, data);
    if (ret)
	return ret;
    res = 4 - (data.length % 4);
    if (res != 4) {
	static const char zero[4] = { 0, 0, 0, 0 };

	ret = krb5_storage_write(sp, zero, res);
	if((size_t)ret != res)
	    return (ret < 0)? errno : krb5_storage_get_eof_code(sp);
    }
    return 0;
}