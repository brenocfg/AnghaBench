#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_rec ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  KADM5_PRIV_GET ; 
 scalar_t__ VERSION2 ; 
 scalar_t__ _kadm5_acl_check_permission (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kadm5_free_principal_ent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kadm5_get_principal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ret_principal_xdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_principal_ent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
proc_get_principal(kadm5_server_context *contextp,
		   krb5_storage *in,
		   krb5_storage *out)
{
    uint32_t version, mask;
    krb5_principal princ;
    kadm5_principal_ent_rec ent;
    krb5_error_code ret;

    memset(&ent, 0, sizeof(ent));

    CHECK(krb5_ret_uint32(in, &version));
    INSIST(version == VERSION2);
    CHECK(ret_principal_xdr(contextp->context, in, &princ));
    CHECK(krb5_ret_uint32(in, &mask));

    ret = _kadm5_acl_check_permission(contextp, KADM5_PRIV_GET, princ);
    if(ret)
	goto fail;

    ret = kadm5_get_principal(contextp, princ, &ent, mask);

 fail:
    krb5_warn(contextp->context, ret, "get principal principal");

    CHECK(krb5_store_uint32(out, VERSION2)); /* api version */
    CHECK(krb5_store_uint32(out, ret)); /* code */
    if (ret == 0) {
	CHECK(store_principal_ent(contextp->context, out, &ent));
    }
    krb5_free_principal(contextp->context, princ);
    kadm5_free_principal_ent(contextp, &ent);
}