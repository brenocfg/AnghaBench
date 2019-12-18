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
struct _krb5_key_data {int dummy; } ;
struct _krb5_checksum_type {int dummy; } ;
typedef  int /*<<< orphan*/  sha1_data ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {char* data; int length; } ;
struct TYPE_6__ {TYPE_1__ checksum; } ;
typedef  TYPE_2__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  CKSUMTYPE_SHA1 ; 
 struct _krb5_checksum_type* _krb5_find_checksum (int /*<<< orphan*/ ) ; 
 scalar_t__ _krb5_internal_hmac (int /*<<< orphan*/ ,struct _krb5_checksum_type*,void const*,size_t,unsigned int,struct _krb5_key_data*,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

krb5_error_code
_krb5_SP_HMAC_SHA1_checksum(krb5_context context,
			    struct _krb5_key_data *key,
			    const void *data,
			    size_t len,
			    unsigned usage,
			    Checksum *result)
{
    struct _krb5_checksum_type *c = _krb5_find_checksum(CKSUMTYPE_SHA1);
    Checksum res;
    char sha1_data[20];
    krb5_error_code ret;

    res.checksum.data = sha1_data;
    res.checksum.length = sizeof(sha1_data);

    ret = _krb5_internal_hmac(context, c, data, len, usage, key, &res);
    if (ret)
	krb5_abortx(context, "hmac failed");
    memcpy(result->checksum.data, res.checksum.data, result->checksum.length);
    return 0;
}