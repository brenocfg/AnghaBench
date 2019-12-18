#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  KADM5_PRIV_DELETE ; 
 scalar_t__ VERSION2 ; 
 scalar_t__ _kadm5_acl_check_permission (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kadm5_delete_principal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ret_principal_xdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
proc_delete_principal(kadm5_server_context *contextp,
		      krb5_storage *in,
		      krb5_storage *out)
{
    uint32_t version;
    krb5_principal princ;
    krb5_error_code ret;

    CHECK(krb5_ret_uint32(in, &version));
    INSIST(version == VERSION2);
    CHECK(ret_principal_xdr(contextp->context, in, &princ));

    ret = _kadm5_acl_check_permission(contextp, KADM5_PRIV_DELETE, princ);
    if (ret)
	goto fail;

    ret = kadm5_delete_principal(contextp, princ);

 fail:
    krb5_warn(contextp->context, ret, "delete principal");
    CHECK(krb5_store_uint32(out, VERSION2)); /* api version */
    CHECK(krb5_store_uint32(out, ret)); /* code */

    krb5_free_principal(contextp->context, princ);
}