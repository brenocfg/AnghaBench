#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tl_data_type; int /*<<< orphan*/  tl_data_contents; int /*<<< orphan*/  tl_data_length; struct TYPE_8__* tl_data_next; } ;
typedef  TYPE_2__ krb5_tl_data ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_10__ {int princ_expire_time; int pw_expiration; int last_pwd_change; int max_life; int mod_date; int attributes; int kvno; int mkvno; int aux_attributes; int max_renewable_life; int last_success; int last_failed; int fail_auth_count; int n_key_data; int n_tl_data; TYPE_1__* key_data; TYPE_2__* tl_data; int /*<<< orphan*/  policy; int /*<<< orphan*/ * mod_name; int /*<<< orphan*/ * principal; } ;
typedef  TYPE_4__ kadm5_principal_ent_rec ;
struct TYPE_7__ {int* key_data_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  store_data_xdr (int /*<<< orphan*/ *,TYPE_3__) ; 
 int /*<<< orphan*/  store_principal_xdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_string_xdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
store_principal_ent(krb5_context contextp,
		    krb5_storage *sp,
		    kadm5_principal_ent_rec *ent)
{
    int i;

    CHECK(store_principal_xdr(contextp, sp, ent->principal));
    CHECK(krb5_store_uint32(sp, ent->princ_expire_time));
    CHECK(krb5_store_uint32(sp, ent->pw_expiration));
    CHECK(krb5_store_uint32(sp, ent->last_pwd_change));
    CHECK(krb5_store_uint32(sp, ent->max_life));
    CHECK(krb5_store_int32(sp, ent->mod_name == NULL));
    if (ent->mod_name)
	CHECK(store_principal_xdr(contextp, sp, ent->mod_name));
    CHECK(krb5_store_uint32(sp, ent->mod_date));
    CHECK(krb5_store_uint32(sp, ent->attributes));
    CHECK(krb5_store_uint32(sp, ent->kvno));
    CHECK(krb5_store_uint32(sp, ent->mkvno));
    CHECK(store_string_xdr(sp, ent->policy));
    CHECK(krb5_store_int32(sp, ent->aux_attributes));
    CHECK(krb5_store_int32(sp, ent->max_renewable_life));
    CHECK(krb5_store_int32(sp, ent->last_success));
    CHECK(krb5_store_int32(sp, ent->last_failed));
    CHECK(krb5_store_int32(sp, ent->fail_auth_count));
    CHECK(krb5_store_int32(sp, ent->n_key_data));
    CHECK(krb5_store_int32(sp, ent->n_tl_data));
    CHECK(krb5_store_int32(sp, ent->n_tl_data == 0));
    if (ent->n_tl_data) {
	krb5_tl_data *tp;

	for (tp = ent->tl_data; tp; tp = tp->tl_data_next) {
	    krb5_data c;
	    c.length = tp->tl_data_length;
	    c.data = tp->tl_data_contents;

	    CHECK(krb5_store_int32(sp, 0)); /* last item */
	    CHECK(krb5_store_int32(sp, tp->tl_data_type));
	    CHECK(store_data_xdr(sp, c));
	}
	CHECK(krb5_store_int32(sp, 1)); /* last item */
    }

    CHECK(krb5_store_int32(sp, ent->n_key_data));
    for (i = 0; i < ent->n_key_data; i++) {
	CHECK(krb5_store_uint32(sp, 2));
	CHECK(krb5_store_uint32(sp, ent->kvno));
	CHECK(krb5_store_uint32(sp, ent->key_data[i].key_data_type[0]));
	CHECK(krb5_store_uint32(sp, ent->key_data[i].key_data_type[1]));
    }

    return 0;
}