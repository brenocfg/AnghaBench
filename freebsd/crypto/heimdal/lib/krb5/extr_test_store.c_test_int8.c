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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ krb5_ret_int8 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_store_int8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
test_int8(krb5_context context, krb5_storage *sp)
{
    krb5_error_code ret;
    int i;
    int8_t val[] = {
	0, 1, -1, 128, -127
    }, v;

    krb5_storage_truncate(sp, 0);

    for (i = 0; i < sizeof(val[0])/sizeof(val); i++) {

	ret = krb5_store_int8(sp, val[i]);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_store_int8");
	krb5_storage_seek(sp, 0, SEEK_SET);
	ret = krb5_ret_int8(sp, &v);
	if (ret)
	    krb5_err(context, 1, ret, "krb5_ret_int8");
	if (v != val[i])
	    krb5_errx(context, 1, "store and ret mismatch");
    }
}