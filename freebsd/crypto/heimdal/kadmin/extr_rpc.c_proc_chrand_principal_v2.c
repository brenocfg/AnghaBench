#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_9__ {scalar_t__ keytype; int /*<<< orphan*/  keyvalue; } ;
typedef  TYPE_1__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_10__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ kadm5_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  KADM5_PRIV_CPW ; 
 scalar_t__ VERSION2 ; 
 scalar_t__ _kadm5_acl_check_permission (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ kadm5_randkey_principal (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**,int*) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ret_principal_xdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_data_xdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
proc_chrand_principal_v2(kadm5_server_context *contextp,
			 krb5_storage *in,
			 krb5_storage *out)
{
    krb5_error_code ret;
    krb5_principal princ;
    uint32_t version;
    krb5_keyblock *new_keys;
    int n_keys;

    CHECK(krb5_ret_uint32(in, &version));
    INSIST(version == VERSION2);
    CHECK(ret_principal_xdr(contextp->context, in, &princ));

    ret = _kadm5_acl_check_permission(contextp, KADM5_PRIV_CPW, princ);
    if(ret)
	goto fail;

    ret = kadm5_randkey_principal(contextp, princ,
				  &new_keys, &n_keys);

 fail:
    krb5_warn(contextp->context, ret, "rand key principal");

    CHECK(krb5_store_uint32(out, VERSION2)); /* api version */
    CHECK(krb5_store_uint32(out, ret));
    if (ret == 0) {
	int i;
	CHECK(krb5_store_int32(out, n_keys));

	for(i = 0; i < n_keys; i++){
	    CHECK(krb5_store_uint32(out, new_keys[i].keytype));
	    CHECK(store_data_xdr(out, new_keys[i].keyvalue));
	    krb5_free_keyblock_contents(contextp->context, &new_keys[i]);
	}
	free(new_keys);
    }
    krb5_free_principal(contextp->context, princ);
}