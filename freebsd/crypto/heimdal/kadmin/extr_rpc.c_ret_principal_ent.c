#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int tl_data_type; struct TYPE_9__* tl_data_next; int /*<<< orphan*/  tl_data_contents; int /*<<< orphan*/  tl_data_length; } ;
typedef  TYPE_2__ krb5_tl_data ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_11__ {int princ_expire_time; int pw_expiration; int last_pwd_change; int max_life; int mod_date; int attributes; int kvno; int mkvno; int aux_attributes; int max_renewable_life; int last_success; int last_failed; int fail_auth_count; int n_key_data; int n_tl_data; TYPE_1__* key_data; TYPE_2__* tl_data; int /*<<< orphan*/  policy; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  principal; } ;
typedef  TYPE_4__ kadm5_principal_ent_rec ;
struct TYPE_8__ {int* key_data_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ret_data_xdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ret_principal_xdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ret_string_xdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ret_principal_ent(krb5_context contextp,
		  krb5_storage *sp,
		  kadm5_principal_ent_rec *ent)
{
    uint32_t flag, num;
    size_t i;

    memset(ent, 0, sizeof(*ent));

    CHECK(ret_principal_xdr(contextp, sp, &ent->principal));
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->princ_expire_time = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->pw_expiration = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->last_pwd_change = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->max_life = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    if (flag == 0)
	ret_principal_xdr(contextp, sp, &ent->mod_name);
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->mod_date = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->attributes = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->kvno = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->mkvno = flag;
    CHECK(ret_string_xdr(sp, &ent->policy));
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->aux_attributes = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->max_renewable_life = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->last_success = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->last_failed = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->fail_auth_count = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->n_key_data = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    ent->n_tl_data = flag;
    CHECK(krb5_ret_uint32(sp, &flag));
    if (flag == 0) {
	krb5_tl_data **tp = &ent->tl_data;
	size_t count = 0;

	while(1) {
	    krb5_data c;
	    CHECK(krb5_ret_uint32(sp, &flag)); /* last item */
	    if (flag)
		break;
	    *tp = calloc(1, sizeof(**tp));
	    INSIST(*tp != NULL);
	    CHECK(krb5_ret_uint32(sp, &flag));
	    (*tp)->tl_data_type = flag;
	    CHECK(ret_data_xdr(sp, &c));
	    (*tp)->tl_data_length = c.length;
	    (*tp)->tl_data_contents = c.data;
	    tp = &(*tp)->tl_data_next;

	    count++;
	}
	INSIST((size_t)ent->n_tl_data == count);
    } else {
	INSIST(ent->n_tl_data == 0);
    }

    CHECK(krb5_ret_uint32(sp, &num));
    INSIST(num == (uint32_t)ent->n_key_data);

    ent->key_data = calloc(num, sizeof(ent->key_data[0]));
    INSIST(ent->key_data != NULL);

    for (i = 0; i < num; i++) {
	CHECK(krb5_ret_uint32(sp, &flag)); /* data version */
	INSIST(flag > 1);
	CHECK(krb5_ret_uint32(sp, &flag));
	ent->kvno = flag;
	CHECK(krb5_ret_uint32(sp, &flag));
	ent->key_data[i].key_data_type[0] = flag;
	CHECK(krb5_ret_uint32(sp, &flag));
	ent->key_data[i].key_data_type[1] = flag;
    }

    return 0;
}