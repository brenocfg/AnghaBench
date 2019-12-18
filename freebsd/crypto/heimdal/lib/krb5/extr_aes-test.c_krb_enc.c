#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int krb5_error_code ;
struct TYPE_7__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int krb5_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
krb_enc(krb5_context context,
	krb5_crypto crypto,
	unsigned usage,
	krb5_data *cipher,
	krb5_data *clear)
{
    krb5_data decrypt;
    krb5_error_code ret;

    krb5_data_zero(&decrypt);

    ret = krb5_decrypt(context,
		       crypto,
		       usage,
		       cipher->data,
		       cipher->length,
		       &decrypt);

    if (ret) {
	krb5_warn(context, ret, "krb5_decrypt");
	return ret;
    }

    if (decrypt.length != clear->length ||
	memcmp(decrypt.data, clear->data, decrypt.length) != 0) {
	krb5_warnx(context, "clear text not same");
	return EINVAL;
    }

    krb5_data_free(&decrypt);

    return 0;
}